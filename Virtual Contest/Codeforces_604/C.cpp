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
		
		vector< pair<int, int> > _list;
		
		int prev = -1, mid = 0;
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			
			if (tmp != prev)
			{
				if (i == n/2)
					mid = _list.size();
				
				_list.emplace_back(tmp, 1);
			}
			else
			{
				if (i == n/2)
					mid = _list.size()-1;
				
				(_list.end() - 1)->second++;
			}
			prev = tmp;
		}
		
		int g = _list[0].second, s = 0, b = 0;
		
		// cout << g << ' ' << mid << endl;
		
		int i;
		for (i = 1; i < mid; i++)
		{
			if (s <= g)
				s += _list[i].second;
			else
				b += _list[i].second;
		}
		
		if ((s <= g or b <= g) or !s or !b)
			cout << "0 0 0" << endl;
		else
			cout << g << ' ' << s << ' ' << b << endl;
	}
}