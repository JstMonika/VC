#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n, k;
		cin >> n >> k;
		
		vector<char> _list(n);
		vector<char> ans(n, ')');
		for (auto &i : _list)
			cin >> i;
		
		int i = n-1, count = 0;
		
		while (count != k-1)
		{
			ans[i--] = ')';
			ans[i--] = '(';
			
			count++;
		}
		
		for (int k = 0; k <= (i/2); k++)
			ans[k] = '(';
		
		/*
		for (auto i : ans)
			cout << i;
		cout << endl;
		*/
		
		count = 0;
		vector< pair<int, int> > change;
		for (int i = 0; i < n; i++)
		{
			if (_list[i] != ans[i])
			{
				int k = i;
				
				while (_list[k] != ans[i]) k++;
				
				// cout << i << ' ' << k << endl;
				
				change.emplace_back(i+1, k+1);
				count++;
				
				reverse(_list.begin() + i, _list.begin() + k+1);
			}
		}
		
		cout << count << endl;
		for (auto i : change)
			cout << i.first << ' ' << i.second << endl;
	}
}