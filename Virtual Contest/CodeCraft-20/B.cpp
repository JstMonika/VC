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
		
		string str;
		cin >> str;
		
		vector< pair<string, int> > _list(n);
		
		for (int i = 1; i <= n; i++)
		{
			_list[i-1].first = str.substr(i-1, n-i+1);
			
			string tmp = str.substr(0, i-1);
			
			if ((n-i+1)%2)
				reverse(&tmp[0], &tmp[0] + i-1);
			
			_list[i-1].first += tmp;
			
			_list[i-1].second = i;
		}
		
		sort(_list.begin(), _list.end());
		
		cout << _list[0].first << endl << _list[0].second << endl;
	}
}