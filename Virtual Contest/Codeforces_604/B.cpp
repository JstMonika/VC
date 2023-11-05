#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n;
		cin >> n;
		
		vector<int> pos(n+1);
		for (int i = 1; i <= n; i++)
		{
			int tmp;
			cin >> tmp;
			pos[tmp] = i;
		}
		
		int MIN = pos[1];
		int MAX = pos[1];
		
		for (int i = 1; i <= n; i++)
		{
			// cout << pos[i] << endl;
			MIN = min(MIN, pos[i]);
			MAX = max(MAX, pos[i]);
			
			if (i == MAX - MIN + 1)
				cout << 1;
			else
				cout << 0;
		}
		
		cout << endl;
	}
}