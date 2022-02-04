#include <iostream>
#include <string>
#include <vector>

using namespace std;

string reverse_string(string input)
{
	string temp= "";
	for (int i = 0; i < input.size(); i++)
		temp += input[input.size() - 1 - i];
	return temp;
}

int cal(string input, int type)
{
	vector<int> b;
	string m;
	for (int i = 0; i < input.size(); i++)
	{
		if (isdigit(input[i]))
			b.push_back(int(input[i]) - 48);
		else
		{
			int temp;
			if (input[i] == '+')
				temp = b[b.size() - 1] + b[b.size() - 2];

			else if (input[i] == '*')
				temp = b[b.size() - 1] * b[b.size() - 2];

			else if (input[i] == '-')
			{
				if (type == 1)
					temp = b[b.size() - 2] - b[b.size() - 1];
				else
					temp = b[b.size() - 1] - b[b.size() - 2];
			}
			b.pop_back();
			b.pop_back();
			b.push_back(temp);
		}
	}
	return b[0];

}

int main()
{
	string input, phrase;
	cin >> input;
	cin >> phrase;
	int ans;
	int type;
	if (!input.compare("Preorder"))
	{
		phrase = reverse_string(phrase);
		type = 2;
	}
	else type = 1;
	ans = cal(phrase, type);
	cout << (ans);
}