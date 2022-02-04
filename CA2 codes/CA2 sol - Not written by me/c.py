def output_array(array_odd, array_even, to_map):
    for i in range(0, len(array_odd)):
        if(to_map[array_odd[i]] != 0):
            print(to_map[array_odd[i]], end = ' ')
        if(len(array_even) <= i):
            print()
            return
        if(to_map[array_even[i]] != 0):
            print(to_map[array_even[i]], end = ' ')
    print()
def find_array_start(begin, right_link, to_map):
    answer = []
    now = begin
    while(now != -1):
        answer.append(now)
        now = right_link[now]
    return answer

def match_every_odd_even(arrays_odd, arrays_even, to_map, map_to):
    pointer_end = len(arrays_even) - 1
    non_have = 0
    for i in range(len(arrays_odd) - 1, - 1, -1):
        if(pointer_end <= -1):
            while(non_have in map_to):
                non_have += 1
            print(non_have)
            map_to[non_have] = 1
        else:
            output_array(arrays_odd[i], arrays_even[pointer_end], to_map)
        pointer_end -= 1

def find_arrays(even_begin, odd_begin, right_link, to_map, map_to):
    arrays_odd = []
    arrays_even = []
    pointer_non_have = 0
    for number in even_begin:
        arrays_even.append(find_array_start(number, right_link, to_map))
    for number in odd_begin:
        arrays_odd.append(find_array_start(number, right_link, to_map))
    print(len(arrays_odd))
    arrays_odd = sorted(arrays_odd, key = lambda array_odd: len(array_odd))
    arrays_even = sorted(arrays_even, key = lambda array_even: len(array_even))
    arrays_two_odd = [[], []]
    arrays_two_even = [[], []]
    for array in arrays_odd:
        if(len(array) != 0 and to_map[array[-1]] == 0):
            arrays_two_odd[0].append(array)
        else:
            arrays_two_odd[1].append(array)
    for array in arrays_even:
        if(len(array) != 0 and to_map[array[-1]] == 0):
            arrays_two_even[0].append(array)
        else:
            arrays_two_even[1].append(array)
    match_every_odd_even(arrays_two_odd[0], arrays_two_even[1], to_map, map_to)
    match_every_odd_even(arrays_two_odd[1], arrays_two_even[0], to_map,  map_to)


numbers = int(input())
map_to = {}
counter = 0
to_map = []
right_link = [-1 for i in range(0, numbers + 3)]
number_times_right = [0 for i in range(0, numbers + 3)]
odd_begin = []
even_begin = []
for i in range(0, numbers):
    start, end = map(int, input().split())
    if(start not in map_to):
        map_to[start] = counter
        counter += 1
        to_map.append(start)
    if(end not in map_to):
        map_to[end] = counter
        counter += 1
        to_map.append(end)
    start = map_to[start]
    end = map_to[end]
    right_link[start] = end
    if(to_map[start] == 0 and to_map[end] != 0):
        even_begin.append(end)
    if(to_map[start] == 0 and to_map[end] == 0):
        odd_begin.append(-1)
    number_times_right[end] += 1
right_link[map_to[0]] = -1
for i in range(0, counter):
    if(to_map[i] != 0 and number_times_right[i] == 0):
        odd_begin.append(i)
find_arrays(even_begin, odd_begin, right_link, to_map, map_to)
