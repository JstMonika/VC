#include <bits/stdc++.h>
using namespace std;

bool bigger(const pair<int, int> &a, const pair<int, int> &b)
{
	if (a.first != b.first)
		return a.first > b.first;
	
	return a.second < b.second;
}

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.second < b.second;
}

int main()
{
	int n;
	cin >> n;
	
	vector< pair<int, int> > _list(n);
	for (int i = 0; i < n; i++)
	{
		cin >> _list[i].first;
		_list[i].second = i+1;
	}
	
	sort(_list.begin(), _list.end(), bigger);
	
	int m;
	cin >> m;
	while (m--)
	{
		int k, pos;
		cin >> k >> pos;
		
		sort(_list.begin(), _list.begin() + k, cmp);
		
		cout << _list[pos-1].first << endl;
		
		sort(_list.begin(), _list.begin() + k, bigger);
	}
}