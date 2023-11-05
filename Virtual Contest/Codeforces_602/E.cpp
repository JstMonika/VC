#include <bits/stdc++.h>
using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	return a.second < b.second;
}

bool bigger(const pair<int, int> &a, const pair<int, int> &b)
{
	if (a.first != b.first)
		return a.first > b.first;
	
	return a.second < b.second;
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
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
		
		vector< pair<int, int> > ans(k);
		ans.assign(_list.begin(), _list.begin() + k);
		
		sort(ans.begin(), ans.end(), cmp);
		
		cout << ans[pos-1].first << endl;
	}
}