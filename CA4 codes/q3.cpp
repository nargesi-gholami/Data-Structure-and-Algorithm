#include <iostream>
#include <vector>

using namespace std;

void add_edge( vector<vector<int>>& graph, vector<int>& adj, int u, int v)
{
	graph[v - 1].push_back(u);
	graph[u - 1].push_back(v);
	adj[v - 1] ++;
	adj[u - 1] ++;
}

vector<int> find_leaves(vector<int>& graph)
{
	vector<int> q;
	for (int i = 0; i < graph.size(); i++)
		if (graph[i] == 1)
			q.push_back(i+1);

	return q;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> graph(n);
	vector<int> degree(n);

	int u, v;
	for (int i = 0 ; i < n-1 ; i++)
	{
		cin >> u >> v;
		add_edge(graph,degree, u, v);
	}

	vector<int> q;
	int i = n;
	q = find_leaves(degree);
	while (i > 2)
	{
		int step = q.size();
		i -= step;
		for (int i = 0 ; i < step ; i++)
		{
			int t = q.front();
			q.erase(q.begin());
			for (int j = 0 ; j <  graph[t-1].size() ; j++)
			{
				degree[graph[t - 1][j]-1]--;
				if (degree[graph[t - 1][j] - 1] == 1)
					q.push_back(graph[t - 1][j]);
			}
		}
	}
	vector<int> root;
	root = q;
	if (root.size() > 1)
		if (root[0] > root[1])
			swap(root[0], root[1]);
	for (int j = 0; j < root.size(); j++)
		cout << root[j] << " ";
}
