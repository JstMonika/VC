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
		
		
		map<int, int> ID;
		map<int, int> cont;
		map<int, int> nega;
		int tmp[10];
		for (int i = 0; i < n; i++)
		{
			cin >> tmp[i];
			if (ID.find(tmp[i]) == ID.end())
			{
				ID[tmp[i]] = 1;
				cont[tmp[i]] = 0;
				nega[tmp[i]] = 1;
			}
			else
				ID[tmp[i]]++;
			
		}

			int sum = 0;
			map<int, int>::iterator it;
			for (it = ID.begin(); it != ID.end(); it++)
			{
				if (it->second == 1)
					continue;
				else
				{
					sum += (it->second) - 1;
				}
			}
		
		cout << sum << endl;
		for (int i = 0; i < n; i++)
		{
			if ((tmp[i] + cont[tmp[i]]) % 10 or cont[tmp[i]] == 0)
			{
				printf("%04d\n", tmp[i]+cont[tmp[i]]);
				cont[tmp[i]]++;
			}
			else
			{
				printf("%04d\n", tmp[i]-nega[tmp[i]]);
				nega[tmp[i]]++;
			}
		}
	}
}