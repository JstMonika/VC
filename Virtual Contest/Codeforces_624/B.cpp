#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int m, n;
		cin >> m >> n;
		
		vector<int> _list(m);
		for (auto &i : _list)
			cin >> i;
		
		vector<bool> swap(n);
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			swap[--tmp] = true;
		}
		
		bool good = true;
		
		for (int i = 0; i < m; i++)
			for (int k = 0; k < m-1; k++)
				if (_list[k] > _list[k+1])
				{
					int tmp = _list[k];
					_list[k] = _list[k+1];
					_list[k+1] = tmp;
					
					if (!swap[k])
						good = false;
				}
				
		cout << ((good) ? "YES" : "NO") << endl;
	}
}