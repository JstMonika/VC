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
		
		if (!(a%b))
			cout << "YES";
		else
			cout << "NO";
		
		cout << endl;
	}
}