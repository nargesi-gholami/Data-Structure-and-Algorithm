#include <iostream>
#include <vector>
#include <string>

#define WAY 1e9 + 7

using namespace std;


void add_edge(vector<vector<long long int>>& city, long long int origin, long long int dest)
{
	city[origin].push_back(dest);
}

void sort(vector<vector<long long int>>& country, int v,  vector<bool>& visited, vector<long long int>& city)
{
	visited[v] = true;
	for (int i = 0 ; i < country[v].size() ; i++)
		if (!visited[country[v][i]])
			sort(country, country[v][i], visited, city);

	city.push_back(v);
}

void find_factory(vector<vector<long long int>>& country, int v, vector<bool>& visited, vector<long long int>& district)
{
	visited[v] = true;
	district.push_back(v);
	for (int i = 0 ; i < country[v].size() ; i++)
		if (!visited[country[v][i]])
			find_factory(country, country[v][i], visited, district);
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	//get n and m
	long long int n, m, origin, dest;
	cin >> n;

	vector<vector<long long int>> country(n);
	vector<vector<long long int>> country_rev(n);
	vector<long long int> cost;
	//get country cost
	long long int max = 0;
	for (long long int i = 0 ; i < n ; i++)
	{
		cost.push_back(0);
		cin >> cost[i];
	}
		
	//get edges
	cin >> m;
	for (long long int i = 0; i < m; i++)
	{
		cin >> origin;
		cin >> dest;
		add_edge(country,   origin - 1, dest - 1);
		add_edge(country_rev, dest - 1, origin - 1);
	}

	//identify city
	vector<long long int> city;
	vector<bool> visited(n);
	for(long long int i = 0 ; i < n ; i++)
		if (!visited[i])
			sort(country, i, visited , city);
	
	//identify district
	vector<vector<long long int>> district;
	vector<bool> visited_(n);
	long long int ans1 = 0;
	long long int ans2 = 1;
	long long int MIN;
	int way = 1e9 + 7;
	for (long long int i = n-1 ; i >= 0 ; i--)
	{
		if (!visited_[city[i]])
		{
			vector<long long int> temp;
			MIN = 1e9 + 1;
			int k = 0;
			find_factory(country_rev, city[i], visited_, temp);

			for (int j = 0; j < temp.size(); j++)
				if(cost[temp[j]] < MIN)
					MIN = cost[temp[j]];
			for (int j = 0; j < temp.size(); j++)
				if(cost[temp[j]] == MIN)
					k++;

			ans1 += MIN;
			ans2 *= k;
			ans2 = ans2 % way;
		}
	}
	cout << ans1 << " " << (ans2 % way) << endl;

	return 0;
}