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
		vector<int> _list(n);
		for (auto &i : _list)
			cin >> i;
		
		sort(_list.begin(), _list.end(), greater<int>());
		
		for (int i = 0; i < _list.size(); i++)
			if (i)
				cout << ' ' << _list[i];
			else
				cout << _list[i];
		
		cout << endl;
	}
}