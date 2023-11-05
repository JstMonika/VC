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
		
		int L = 0, R = numeric_limits<int>::max();
		
		for (int i = 0; i < n; i++)
		{
			int a, b;
			cin >> a >> b;
			
			L = max(a, L);
			R = min(b, R);
		}
		
		if (L < R)
			cout << 0 << endl;
		else
			cout << L-R << endl;
		
	}
}