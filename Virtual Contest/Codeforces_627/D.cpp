#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	
	vector<int> _list(n);
	for (auto &i : _list)
		cin >> i;
	
	for (int i = 0; i < n; i++)
	{
		int tmp;
		cin >> tmp;
		
		_list[i] -= tmp;
	}
	
	sort(_list.begin(), _list.end());
	
	long long ans = 0;
	
	for (int i = 0; i < n; i++)
	{
		ans += _list.end() - lower_bound(_list.begin() + i+1, _list.end(), max(0, _list[i]*-1 + 1));
	}
	
	cout << ans << endl;
}