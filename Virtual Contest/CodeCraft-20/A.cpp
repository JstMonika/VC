#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int i, m;
		cin >> i >> m;
		int sum = 0;
		for (int k = 0; k < i; k++)
		{
			int tmp;
			cin >> tmp;
			sum += tmp;
		}
		
		cout << ((sum > m) ? m : sum) << endl;
	}
}