#include <bits/stdc++.h>
using namespace std;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m, p;
	cin >> n >> m >> p;
	
	int tmp, ai, aj;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		if (tmp % p)
			ai = i;
	}
	
	for (int i = 0; i < m; i++)
	{
		cin >> tmp;
		if (tmp % p)
			aj = i;
	}
	
	cout << ai+aj << endl;
}