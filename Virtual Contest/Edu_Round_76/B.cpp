#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		long long a, b;
		cin >> a >> b;
		
		set<int> done;
		
		bool good = true;
		while (a < b)
		{
			if (done.count(a))
			{
				good = false;
				break;
			}
			else
				done.insert(a);
			
			if (a % 2)
				a--;
			
			a = a*3/2;
		}
		
		if (good)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}