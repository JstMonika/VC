#include <bits/stdc++.h>
using namespace std;

int first[100000];
bool done[100000];

int main()
{
	int n;
	cin >> n;
	
	vector< vector<int> > _list(n);
	vector< vector<int> > find(n, vector<int>(0));
	
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < 3; k++)
		{
			cin >> _list[i][k];
			first[_list[i][k]]++;
			
			find[_list[i][k]].push_back(i);
		}
	}
	
	int idx = 0;
	for (; first[idx] != 1; idx++)
		;
	
	cout << idx;
	int cur = find[idx][0];
	for (auto now : _list[cur])
		first[now]--;
	
	while (true)
	{
		int x = (_list[cur][0] != idx) ? _list[cur][0] : _list[cur][1];
		int y = (_list[cur][2] != idx) ? _list[cur][2] : _list[cur][1];
		
		for (auto triple : find[idx])
		{
			
		}
	}
}