#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n, m;
		cin >> n >> m;
		
		long long sum = 0;
		
		vector< pair<int, int> > _list;
		for (int i = 1; i <= n; i++)
		{
			int tmp;
			cin >> tmp;
			sum += tmp * 2;
			_list.emplace_back(tmp, i);
		}
		
		if (m < n or n <= 2)
		{
			cout << -1 << endl;
			continue;
		}
		
		sort(_list.begin(), _list.end());
		
		sum += (m-n) * (_list[0].first + _list[1].first);
		cout << sum << endl;
		
		for (int i = 1; i <= n; i++)
			if (i == n)
				cout << n << ' ' << 1 << endl;
			else
				cout << i << ' ' << i+1 << endl;
			
		for (int i = 0; i < m-n; i++)
			cout << _list[0].second << ' ' << _list[1].second << endl;
	}
}