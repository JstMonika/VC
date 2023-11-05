#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n, x, a, b;
		cin >> n >> x >> a >> b;
		int dis = abs(b-a) + x;
		
		cout << ((dis > n-1) ? n-1 : dis) << endl;
	}
}