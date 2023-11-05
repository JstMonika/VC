#include <bits/stdc++.h>
using namespace std;

int pressed[26];

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int len, m;
		cin >> len >> m;
		
		string str;
		cin >> str;
		
		vector< vector<int> > memo(len, vector<int>(26, 0));
		memset(pressed, 0, sizeof(pressed));

		for (int i = 0; i < len; i++)
		{
			if (i)
				for (int k = 0; k < 26; k++)
					memo[i][k] = memo[i-1][k];
			
			memo[i][str[i] - 'a']++;
		}
		
		
		for (int i = 0; i < m; i++)
		{
			int tmp;
			cin >> tmp;
			
			for (int k = 0; k < 26; k++)
				pressed[k] += memo[tmp-1][k];
		}
		
		for (int k = 0; k < 26; k++)
				pressed[k] += memo[len-1][k];
		
		
		for (int i = 0; i < 26; i++)
		{
			if (i)
				cout << ' ' << pressed[i];
			else
				cout << pressed[i];
		}
		
		cout << endl;
	}
}