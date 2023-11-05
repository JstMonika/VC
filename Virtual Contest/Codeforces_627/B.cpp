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
		
		map<int, int> memo;
		bool good = false;
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			
			if (memo.find(tmp) == memo.end())
				memo[tmp] = i;
			else
			{
				if (i - memo[tmp] >= 2)
					good = true;
			}
		}
		
		cout << (good ? "YES" : "NO") << endl;
	}
}