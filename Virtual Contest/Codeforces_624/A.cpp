#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int a, b;
		cin >> a >> b;
		
		if (a == b)
			cout << 0 << endl;
		else if (a < b and (b-a) % 2)
			cout << 1 << endl;
		else if (a < b)
			cout << 2 << endl;
		else if (a > b and (a-b) % 2)
			cout << 2 << endl;
		else
			cout << 1 << endl;
	}
}