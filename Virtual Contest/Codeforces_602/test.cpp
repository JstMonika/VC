#include <bits/stdc++.h>
using namespace std;

bool cmp(const vector<int> &a, const vector<int> &b)
{
	return a < b;
}

int main()
{
	vector< vector<int> > _list;
	
	vector<int> tmp = {3, 1};
	
	_list.push_back(tmp);
	
	tmp[0] = 1;
	tmp[1] = 2;
	
	_list.push_back(tmp);
	
	sort(_list.begin(), _list.end(), cmp);
	cout << _list.size();
	cout << _list[0].size();
	cout << _list[0][0];
}