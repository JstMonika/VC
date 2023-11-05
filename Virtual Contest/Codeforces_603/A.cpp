#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int a[3];
		for (int i = 0; i < 3; i++)
			cin >> a[i];
		
		sort(&a[0], &a[0] + 3);
		
		if (a[0] + a[1] <= a[2])
			cout << (a[0] + a[1]) << endl;
		else
			cout << ((a[0] + a[1] - a[2]) / 2) + a[2] << endl;
	}
}