#include<iostream>
using namespace std;
const int MAX_N = 2e5 + 10;
void update(int start, int end, int start_need, int end_need, int value, int node, int* segment_tree)
{
    if(start >= end_need || start_need >= end)
    {
        return;
    }
    if(start_need <= start && end_need >= end)
    {
        segment_tree[node] ^= value;
        return;
    }
    int mid = (start + end) / 2;
    update(start, mid, start_need, end_need, value, node * 2, segment_tree);
    update(mid, end, start_need, end_need, value, node * 2 + 1, segment_tree);

}

int get(int start, int end, int index, int node, int* segment_tree)
{
    if(start + 1 == end)
    {
        return segment_tree[node];
    }
    int mid = (start + end) / 2;
    if(mid > index)
    {
        return get(start, mid, index, node * 2, segment_tree) ^ segment_tree[node];
    }
    return get(mid, end, index, node * 2 + 1, segment_tree) ^ segment_tree[node];
}

int main()
{
    int segment_tree[MAX_N * 2];
    int number_queries, numbers;
    cin >> numbers >> number_queries;
    for(int i = 0; i < MAX_N; i++)
    {
        segment_tree[i] = 0;
    }
    while(number_queries -- )
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int start_need, end_need, value;
            cin >> start_need >> end_need >> value;
            update(0, numbers, start_need - 1, end_need, value, 1, segment_tree);
        }
        else
        {
            int index;
            cin >> index;
            cout << get(0, numbers, index - 1, 1, segment_tree) << endl;
        }
    }
}
