#include<iostream>

using namespace std;

#define RED_COLOR  1
#define BLACK_COLOR 0
const int MAX_N = 1e5+10;

class node_red_black
{
public:
    int value;
    int color;
    node_red_black* right_child;
    node_red_black* left_child;
    node_red_black* parent;
};
void left_rotate(node_red_black* input_node)
{
    node_red_black* right_child = input_node->right_child;
    node_red_black* left_grand_child = (input_node->right_child)->left_child;
    if(input_node->parent and input_node->parent->right_child == input_node)
        input_node->parent->right_child = right_child;
    else if(input_node->parent)
        input_node->parent->left_child = right_child;
    right_child->parent = input_node->parent;
    right_child->left_child = input_node;
    input_node->right_child = left_grand_child;
    input_node->parent = right_child;
    if(left_grand_child)
        left_grand_child->parent = input_node;
}
void right_rotate(node_red_black* input_node)
{
    node_red_black* left_child = input_node->left_child;
    node_red_black* right_grand_child = (input_node->left_child)->right_child;
    if(input_node->parent and input_node->parent->right_child == input_node)
        input_node->parent->right_child = left_child;
    else if(input_node->parent)
        input_node->parent->left_child = left_child;
    left_child->parent = input_node->parent;
    left_child->right_child = input_node;
    input_node->left_child = right_grand_child;
    input_node->parent = left_child;
    if(right_grand_child)
        right_grand_child->parent = input_node;
}
void fix_up(node_red_black* new_node)
{
    if((new_node->parent)->color == BLACK_COLOR)
        return;
    while(new_node->parent and new_node->parent->color == RED_COLOR)
    {
        node_red_black* grand_parent = new_node->parent->parent;
        node_red_black* uncle;
        if(grand_parent->left_child == new_node->parent)
            uncle = grand_parent->right_child;
        else
            uncle = grand_parent->left_child;
        if(uncle and uncle->color == RED_COLOR)
        {
            uncle->color = BLACK_COLOR;
            new_node->parent->color = BLACK_COLOR;
            grand_parent->color = RED_COLOR;
            new_node = grand_parent;
            continue;
        }
        if(new_node->parent == grand_parent->left_child and new_node == new_node->parent->right_child)
        {
            new_node = new_node->parent;
            left_rotate(new_node);
        }
        if(new_node->parent == grand_parent->right_child and new_node == new_node->parent->left_child)
        {
            new_node = new_node->parent;
            right_rotate(new_node);
        }
        new_node->parent->color = BLACK_COLOR;
        new_node->parent->parent->color = RED_COLOR;
        if(new_node == new_node->parent->left_child)
            right_rotate(grand_parent);
        if(new_node == new_node->parent->right_child)
            left_rotate(grand_parent);
        break;
    }
    if(not new_node->parent)
        new_node->color = BLACK_COLOR;
}
void add_element(int value,node_red_black* &root, node_red_black** nodes, int pointer)
{
    node_red_black* new_node = nodes[pointer];
    new_node->color = RED_COLOR;
    new_node->value = value;
    new_node->right_child = NULL;
    new_node->left_child = NULL;
    new_node->parent = NULL;
    if(root == NULL)
    {
        root = new_node;
        new_node->color = BLACK_COLOR;
        return;
    }
    node_red_black* vertex_now = root;
    while(true)
    {
        node_red_black* must_go = vertex_now->right_child;
        if(vertex_now->value > new_node->value)
            must_go = vertex_now->left_child;
        if(must_go == NULL)
            break;
        vertex_now = must_go;
    }
    if(vertex_now->value > new_node->value)
        vertex_now->left_child = new_node;
    else
        vertex_now->right_child = new_node;
    new_node->parent = vertex_now;
    fix_up(new_node);
}
node_red_black* find_root(node_red_black* now)
{
    if(now->parent == NULL)
        return now;
    return find_root(now->parent);
}
bool search(int value,node_red_black* root)
{
    node_red_black* vertex_now = root;
    while(true)
    {
        node_red_black* must_go = vertex_now->right_child;
        if(vertex_now->value == value)
            return true;
        if(vertex_now->value > value)
            must_go = vertex_now->left_child;
        if(must_go == NULL)
            break;
        vertex_now = must_go;
    }
    return false;
}

int main()
{
    int q;
    cin >> q;
    node_red_black* root = NULL;
    bool flag = false;
    node_red_black* nodes[MAX_N];
    for(int i = 0; i < q; i++)
    {
        int type, value;
        cin >> type >> value;
        if(type == 1)
        {
            nodes[i] = new node_red_black();
            flag = true;
            add_element(value, root, nodes, i);
            root = find_root(root);
        }
        else
        {
            if(flag && search(value, root))
                cout << "YES" << endl;
            else
                cout <<"NO" << endl;
        }
    }
}
