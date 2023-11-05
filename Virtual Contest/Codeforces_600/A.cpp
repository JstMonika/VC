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
		
		vector<int> a(n);
		
		for (int i = 0; i < n; i++)
			cin >> a[i];
		
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			a[i] = tmp-a[i];
		}
		
		stack<int> _list;
		
		bool good = true;
		for (int i = 0; i < n; i++)
		{
			if (a[i] < 0)
			{
				good = false;
				break;
			}
			
			if (_list.empty())
				_list.push(a[i]);
			else if (_list.top() == a[i])
				continue;
			else
				_list.push(a[i]);
		}
		
		int count = 0;
		while (!_list.empty())
		{
			if (_list.top())
				count++;
			
			_list.pop();
		}
		
		if (count >= 2 or !good)
			cout << "NO" << endl;
		else
			cout << "YES" << endl;
	}
}