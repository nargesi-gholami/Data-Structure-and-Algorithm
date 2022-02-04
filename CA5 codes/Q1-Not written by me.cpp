#include<bits/stdc++.h>

#define ll long long

using namespace std;

const int N = 1e5 + 22; // Max number of cities

ll n, max_capacity;
ll city_distance[N];
vector<pair<ll, ll>> cities; // {Distance From start, choclate cost}
ll next_city[N];

int main()
{
    cin >> n;
    for (int i=0; i<n; i++)
        cin >> city_distance[i];
    for (int i=0; i<n; i++)
    {
        ll city_cost;
        cin >> city_cost;
        cities.push_back({city_distance[i], city_cost});
    }
    cin >> max_capacity;
    sort(cities.begin(), cities.end());
    cities.back().second = 0; // for simplicity of implementation

    stack<pair<ll, ll>> lis; // longest increasing subsequence : {City_Cost, City_ID}

    for (int i=n-1; i>=0; i--)
    {
        ll city_cost = cities[i].second;
        while (lis.size() && lis.top().first > city_cost)
        {
            lis.pop();
        }
        if (i != n-1)
            next_city[i] = lis.top().second;
        lis.push({city_cost, i});
    }

    ll current_choclate = max_capacity;
    ll total_cost = 0;
    ll prev_distance = 0;

    for (int i=0; i<n; i++)
    {
        ll city_pos = cities[i].first;
        ll city_cost = cities[i].second;
        // eating choclates to get city i
        if (current_choclate < city_pos - prev_distance)
        {
            cout << -1 << endl;
            return 0;
        }
        current_choclate -= city_pos - prev_distance;
        prev_distance = city_pos;
        // buying choclates to get city i+1 and beyond
        if (i == n-1)
            break;
        ll needed_choclates = cities[next_city[i]].first - city_pos;
        if (current_choclate > needed_choclates)
            continue;
        ll bought_choclates = min(max_capacity - current_choclate, needed_choclates - current_choclate);
        total_cost += bought_choclates * city_cost;
        current_choclate += bought_choclates;
    }
    cout << total_cost << endl;

    return 0;
}