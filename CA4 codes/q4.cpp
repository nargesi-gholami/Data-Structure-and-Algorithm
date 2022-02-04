#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
using namespace std;

int dir[4][2] =
{
	{ -1,0 },
	{ 1, 0 },
	{ 0,-1 },
	{ 0, 1 }
};
void print_count(vector<vector<int>> farm)
{
	for (int i = 0; i < farm.size(); i++)
	{
		for (int j = 0; j < farm[0].size(); j++)
			cout << farm[i][j] << "  ";
		cout << endl;
	}
	cout << "//////////" << endl;
}

vector<int> make_farm(vector<vector<char>> farm, vector<vector<int>>& distance, vector<vector<bool>> visited, pair<int, int> des, vector<int> cow_distance)
{
	visited[des.first][des.second] = true;

	vector<pair<int, int>> path;

	path.push_back(des);
	distance[des.first][des.second] = 0;

	while (!path.empty())
	{
		pair<int, int> s = path.front();

		path.erase(path.begin());


		for (int i = 0; i < 4; i++)
		{
			if (s.first + dir[i][0] >= 0 && s.second + dir[i][1] >= 0 && s.first + dir[i][0] < distance.size()
				&& s.second + dir[i][1] < distance[0].size())
				if (farm[s.first + dir[i][0]][s.second + dir[i][1]] != '#' && !visited[s.first + dir[i][0]][s.second + dir[i][1]])
				{
					visited[s.first + dir[i][0]][s.second + dir[i][1]] = true;
					distance[s.first + dir[i][0]][s.second + dir[i][1]] = distance[s.first][s.second] + 1;
					path.push_back(make_pair(s.first + dir[i][0], s.second + dir[i][1]));
				}
		}
		if (farm[s.first][s.second] == '*')
			cow_distance.push_back(distance[s.first][s.second] + 1);
	}		
	return cow_distance;
}

int find_path(vector<int> cow_distance)
{
	vector<int> path(cow_distance.size());
	for (int i = 0; i < cow_distance.size() ; i++)
	{
		if (i == 0)
		{
			path[i] = cow_distance[i];
			continue;
		}
		path[i] = (path[i - 1] + 1) > cow_distance[i] ? (path[i - 1] + 1) : cow_distance[i];
	}
	return path[cow_distance.size() - 1];
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	vector<vector<bool>> visited;
	vector<pair<int, int>> cows;
	vector<vector<char>> farm;
	vector<vector<int>> count;
	pair<int, int> des;
	string k;
	int i, j;

	//construct vector of farm
	cin >> n >> m;
	for (int i = 0; i < n; i++)
	{
		vector<char> temp(m);
		vector<int> temp_int(m);
		vector<bool> temp_bool(m);
		farm.push_back(temp);
		count.push_back(temp_int);
		visited.push_back(temp_bool);
	}

	//put cow in farm
	for (int i = 0; i < n; i++)
	{
		cin >> k;
		for (int j = 0; j < m; j++)
		{
			farm[i][j] = k[j];
			if (farm[i][j] == '*')
				cows.push_back(make_pair(i, j));
			if ((i == 0 || j == 0 || i == n - 1 || j == m - 1)
				&& farm[i][j] == '-')
				des = make_pair(i, j);
		}
	}

	vector<int> cow_distance;
	cow_distance = make_farm(farm, count, visited, des, cow_distance);

	sort(cow_distance.begin(), cow_distance.end());

	cout << find_path(cow_distance) << endl;
}