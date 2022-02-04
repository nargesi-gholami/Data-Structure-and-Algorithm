def push_down(heap_tree, index):
    path = [index - 1]
    while(True):
        if(index * 2 > len(heap_tree)):
            return path
        if(index * 2 + 1 > len(heap_tree)):
            if(heap_tree[index * 2 - 1] < heap_tree[index - 1]):
                heap_tree[index - 1], heap_tree[index * 2 - 1] = heap_tree[index * 2 - 1], heap_tree[index -1]
                path.append(index * 2 - 1)
            return path
        minimum_childs = min(heap_tree[index * 2 - 1], heap_tree[index * 2])
        if(heap_tree[index - 1] > minimum_childs):
            if(heap_tree[index * 2 - 1] == minimum_childs):
                heap_tree[index - 1], heap_tree[index * 2 - 1] = heap_tree[index * 2 - 1], heap_tree[index -1]
                index = index * 2
                path.append(index - 1)
            else:
                heap_tree[index - 1], heap_tree[index * 2] = heap_tree[index * 2], heap_tree[index -1]
                index = index * 2 + 1
                path.append(index - 1)
        else:
            return path

def pull_up(heap_tree, index):
    path = [index - 1]
    while(True):
        if(index == 1):
            return path
        if(heap_tree[index // 2 - 1] > heap_tree[index - 1]):
            heap_tree[index - 1], heap_tree[index // 2 - 1] = heap_tree[index // 2 - 1], heap_tree[index - 1]
        else:
            return path
        index //= 2
        path.append(index - 1)

def delete_index_heap(heap_tree, index):
    deleted = heap_tree[index]
    heap_tree[index] = heap_tree[-1]
    heap_tree.pop()
    if(index == len(heap_tree)):
        return []
    if(len(heap_tree) == 0):
        return []
    if((index + 1) // 2 != 0 and heap_tree[(index + 1) // 2 - 1] > heap_tree[index]):
        return pull_up(heap_tree, index + 1)
    return push_down(heap_tree, index + 1)

def add_element_to_heap(heap_tree, element):
    heap_tree.append(element)
    path = pull_up(heap_tree, len(heap_tree))
    return path

def update_node(heap_all_elements, path, node):
    for changed in path:
        node[heap_all_elements[changed][1]] = changed

def delete_index_heap_all(heap_all_elements, heap_trees, value_trees, node, index):
    if(len(heap_all_elements) <= index):
        return -1
    number_deleted = heap_all_elements[index]
    node[number_deleted[1]] = -1
    path = delete_index_heap(heap_all_elements, index)
    update_node(heap_all_elements, path, node)
    class_deleted = number_deleted[1]
    delete_index_heap(heap_trees[class_deleted], 0)
    if(len(heap_trees[class_deleted])):
        path = add_element_to_heap(heap_all_elements, (heap_trees[class_deleted][0] + value_trees[class_deleted], class_deleted))
        update_node(heap_all_elements, path, node)
    return number_deleted[0]

def update_heap_all(heap_all_elements, id_class, heap_trees, node):
    if(node[id_class] != -1):
        path = delete_index_heap(heap_all_elements, node[id_class])
        update_node(heap_all_elements, path, node)
        node[id_class] = -1
    if(len(heap_trees[id_class]) != 0):
        path = add_element_to_heap(heap_all_elements, (heap_trees[id_class][0] + value_trees[id_class], id_class))
        update_node(heap_all_elements, path, node)

def query_add_element(value, id_class, heap_all_elements, heap_trees, value_trees, node):
    add_element_to_heap(heap_trees[id_class], value - value_trees[id_class])
    update_heap_all(heap_all_elements, id_class, heap_trees, node)

def query_add_value(value, id_class, heap_all_elements, heap_tree, value_trees, node):
    value_trees[id_class] += value
    update_heap_all(heap_all_elements, id_class, heap_trees, node)

number_classes, queries = map(int, input().split())
heap_trees = [[] for i in range(0, number_classes)]
value_trees = [0 for i in range(0, number_classes)]
heap_all_elements = []
node = [-1 for i in range(0, number_classes)]
for i in range(0, queries):
    inputs = input().split()
    type = int(inputs[0])
    if(type == 3):
        print(delete_index_heap_all(heap_all_elements, heap_trees, value_trees, node, 0))
    if(type == 1):
        query_add_element(int(inputs[2]), int(inputs[1]) - 1, heap_all_elements, heap_trees, value_trees, node)
    if(type == 2):
        query_add_value(int(inputs[2]), int(inputs[1]) - 1, heap_all_elements, heap_trees, value_trees, node)
