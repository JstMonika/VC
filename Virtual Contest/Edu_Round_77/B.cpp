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
		
		int bigger = (a > b) ? a : b;
		int smaller = (a < b) ? a : b;
		
		if (((a+b) % 3) or ((bigger - 2 * smaller > 0)))
			cout << "NO" << endl;
		else 
			cout << "YES" << endl;
	}
}