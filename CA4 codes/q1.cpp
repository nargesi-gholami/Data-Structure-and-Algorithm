#include <iostream>
#include <vector>

using namespace std;

#define IN 1
#define OUT 0

void add_edge(vector<vector<int>>&graph, int u,int v)
{
	graph[v - 1].push_back(u);
	graph[u - 1].push_back(v);
}

vector<bool> DFS(vector<vector<int>>& graph, int v, vector<bool>& visited,int in, vector<int>& direct)
{
	v--;
	visited[v] = true;
	direct[v] = in;
	for (int i = 0 ; i < graph[v].size() ; i++)
		if (!visited[graph[v][i] - 1])
			visited = DFS(graph, graph[v][i], visited, 1-in, direct);
		
	return visited;
}

bool contains_odd(vector<vector<int>> graph, int src)
{
	vector<int> color_arr(graph.size());
	for (int i = 0; i < graph.size(); ++i)
		color_arr[i] = -1;

	color_arr[src - 1] = 1;
	vector <int> q;
	q.push_back(src);

	while (!q.empty())
	{
		int u = q.front();
		q.erase(q.begin());

		if (graph[u - 1].size() == 0)
			return true;

		for (int i = 0 ; i < graph[u - 1].size() ; i++)
		{
			int v = graph[u - 1][i];
			if (color_arr[v - 1] == -1)
			{
				color_arr[v - 1] = 1 - color_arr[u - 1];
				q.push_back(v);
			}

			else if (color_arr[v - 1] == color_arr[u - 1] && color_arr[v - 1] != -1)
				return true;
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	int u, v;
	cin >> n >> m;

	bool has_cycle;
	vector<int> direct(n);
	vector<vector<int>> graph(n);
	vector<bool> visited(n, 0);
	vector <int> edges;

	for (int i = 0 ; i < m ; i++)
	{
		cin >> u >> v;
		add_edge(graph, u,v);
		edges.push_back(u);
	}
	
	has_cycle = contains_odd(graph, 1);

	if (!has_cycle)
	{
		cout << "YES" << endl;
		DFS(graph, 1, visited, IN, direct);
		for (int i = 0; i < m; i++)
			cout << direct[edges[i]-1];
		cout << endl;
	}
	else
		cout << "NO" << endl;
}