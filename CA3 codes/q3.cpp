#include<iostream>
#include<vector>
#include <cmath>

using namespace std;

int main()
{
	int q, t, n;
	int hash;
	bool p = false;
	cin >> q;
	int key = pow(10, 4);
	vector<vector<int>> code(key);
	for (int i = 0; i < q; i++)
	{
		cin >> t >> n;
		p = false;
		if (t == 1)
		{
			hash = n % key;
			code[hash].push_back(n);
		}
		else if (t == 2)
		{
			hash = n % key;
			for (int j = 0; j < code[hash].size(); j++)
				if (n == code[hash][j])
					p = true;
			if (p)
				cout << ("YES") << endl;
			else
				cout << ("NO") << endl;
		}
	}
}