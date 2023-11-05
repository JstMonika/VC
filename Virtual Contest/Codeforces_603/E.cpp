#include <bits/stdc++.h>
using namespace std;

vector<char> _list;
vector<char> ans;
vector<int> dp;


void go(int c, int cur, int num, int last)
{
	if (c == _list.size())
		return;
	
	if (_list[c] == 'L')
	{
		go(c+1, cur-1); 
		return;
	}
	if (_list[c] == 'R')
	{
		go(c+1, cur+1);
		return;
	}
		// L, R.
	
	if (_list[c] != '(' and _list[c] != ')')
	{
		
	}
	// characters.
	
	
	// ().
}

int main()
{
	int n;
	cin >> n;
	cin.get();
	
	_list.resize(n);
	ans.resize(n);
	dp.resize(n);
	
	for (int i = 0; i < n; i++)
		_list[i] = cin.get();
	
	go(0, 0, 0, -1);	// comment, current, color, last'('.
}