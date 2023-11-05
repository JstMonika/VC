#include <bits/stdc++.h>
using namespace std;

struct trap
{
	int l;
	int d;
	int r;
};

bool cmp(const trap &a, const trap &b)
{
	if (a.d != b.d)
		return a.d > b.d;
	
	return a.r > b.r;
}

int main()
{
	int m, n, k, t;
	cin >> m >> n >> k >> t;
	
	vector<int> squad(m);
	for (auto &i : squad)
		cin >> i;
	
	sort(squad.begin(), squad.end(), greater<int>());
	
	/*
	cout << "--- squad part ---" << endl;
	for (int i = 0; i < m; i++)
		cout << squad[i] << ' ';
	cout << endl << "---" << endl;
	*/
	
	vector<trap> _list(k);
	for (int i = 0, m = 0; m < k; i++, m++)
	{
		cin >> _list[i].l >> _list[i].d >> _list[i].r;	// location, disarmed, level.
		
		if (_list[i].l > _list[i].d)
		{
			_list.erase(_list.begin() + i);
			i--;
		}
	}
	
	sort(_list.begin(), _list.end(), cmp);
	
	/*
	cout << "--- trap part ---" << endl;
	for (int i = 0; i < _list.size(); i++)
	{
		cout << _list[i].d << ' ' << _list[i].r << endl;
	}
	cout << "----" << endl;
	*/
	
	int i = 0;
	int undisarmed_MAX = 0;
	for (;t < (_list[i].d * 2 + n+1) ; i++)
		undisarmed_MAX = max(undisarmed_MAX, _list[i].r);
	
	// cout << "i = " << i << endl;
	// cout << undisarmed_MAX << endl;
	
	int num = 0;
	for (; squad[num] >= undisarmed_MAX; num++)
		;
	
	cout << num;
}