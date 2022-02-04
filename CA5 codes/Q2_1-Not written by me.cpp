#include<bits/stdc++.h>

#define ll long long
	
using namespace std;
	
const int N = 1e6+22, INF = 1e9+22, MOD = 1e9+7, PRIME_BASE = 67;
	
char passage[N];
ll power_base[N];
bool is_name_started[N];
	
// calculate hash of all prefix of s and returns hash of s
ll calc_string_prefix_hash(string s, vector<ll>& hash)
{
	hash.resize(s.size());
	hash[0] = s[0];
	for (int i=1; i<s.size(); i++)
		hash[i] = (hash[i-1]*PRIME_BASE + s[i]) % MOD;
	return hash[s.size()-1];
}

// calculate hash of all suffix of s and returns hash of s
ll calc_string_suffix_hash(string s, vector<ll>& hash)
{
	hash.resize(s.size());
	hash[s.size()-1] = s[s.size()-1];
	for (int i=s.size()-2; i>=0; i--)
		hash[i] = (hash[i+1] + s[i]*power_base[s.size() - i - 1]) % MOD;
	return hash[0];
}
	
// find hash of s[l:r] with vector of prefix hash
ll find_substr_hash(vector<ll>& hash, int l, int r)
{
	if (!l) 
		return hash[r];
	ll rr = (hash[r] - (hash[l-1]*power_base[r-l+1])) % MOD;
	while (rr<0) 
		rr += MOD;
	return rr;
}

int main()
{
	int n, m;
	string choclate_name ;

	power_base[0]=1;
	for (int i=1; i<N; i++) 
		power_base[i] = (power_base[i-1]*PRIME_BASE) % MOD;
	
	cin >> n >> m;
	cin >> choclate_name;

	for (int i=0; i<m; i++)
	{
		int x;
		cin >> x;
		is_name_started[x-1]=true;
	}

	vector<ll> hash_prefix;
	calc_string_prefix_hash(choclate_name, hash_prefix);
	vector<ll> hash_suffix;
	calc_string_suffix_hash(choclate_name, hash_suffix);

	int last_occurrence = -1;
	ll res = 1;
	for (int i=0; i<n; i++)
	{
		if (choclate_name.size() < i-last_occurrence+1)
			last_occurrence = -1;
		if (is_name_started[i]) 
		{
			if (last_occurrence != -1)
			{
				if (hash_suffix[i - last_occurrence] != hash_prefix[choclate_name.size()-(i-last_occurrence)-1])
				{
					res = 0;
					break;
				}
			}
			last_occurrence = i;
		} 
		else if(last_occurrence == -1) 
		{
			res = (res*26) % MOD;
		}
	}
	cout << res << endl;
	
	return 0;
}