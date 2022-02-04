#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void add_edge(vector<vector<int>>&graph, int u, int v)
{
	graph[v - 1].push_back(u);
	graph[u - 1].push_back(v);
}

void dfs_cycle(int u,int p,int k,vector<vector<int>>& graph, vector<int>& color, vector<vector<int>>& mark, vector<int>& par, int& cyclenumber)
{
	if (cyclenumber && mark[cyclenumber - 1].size() > k)return;
	if (color[u-1] == 2) 
		return;
	if (color[u-1] == 1)
	{
		cyclenumber++;
		int cur = p;
		vector<int> temp;
		mark.push_back(temp);
		mark[cyclenumber-1].push_back(cur);
		while (cur != u)
		{
			cur = par[cur-1];
			mark[cyclenumber-1].push_back(cur);
		}
		return;
	}
	par[u-1] = p;
	color[u-1] = 1;
	if (cyclenumber && mark[cyclenumber - 1].size() > k)return;
	for(int v = 0 ; v < graph[u-1].size() ; v++)
	{
		if (graph[u-1][v] == par[u-1])
			continue;
		
		dfs_cycle(graph[u-1][v], u,k, graph, color, mark, par, cyclenumber);
	}
	color[u-1] = 2;
}

void print_cycle(vector<vector<int>> mark, int cycle_num)
{
	cout << mark[cycle_num-1].size() << endl;
	if(mark[cycle_num - 1][0] > mark[cycle_num - 1][mark[cycle_num-1].size()-1])
		for (int i = mark[cycle_num - 1].size()-1 ; i >= 0 ; i--)
			cout << mark[cycle_num - 1][i] << " ";
	else
		for (int i = 0; i < mark[cycle_num-1].size(); i++)
				cout << mark[cycle_num - 1][i] << " ";
	
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<int>> graph(n);

	int u, v;
	for (int i = 0; i < m; i++)
	{
		cin >> u >> v;
		add_edge(graph, u, v);
	}

	////////////////////////
	vector<int> parents(n,-1);
	vector<int> color(n, 0);
	vector<vector<int>> mark;
	int cycle_num = 0;
	dfs_cycle(1, 0,k, graph,color,mark, parents, cycle_num);

	if (cycle_num)
		print_cycle(mark, cycle_num);
	else
		cout << -1 << endl;

	//system("pause");
}