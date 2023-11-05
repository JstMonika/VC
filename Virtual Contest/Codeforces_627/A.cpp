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
		
		vector<int> _list(n);
		
		bool good = true;
		
		int tmp;
		cin >> tmp;
		
		for (int i = 1; i < n; i++)
		{
			int t;
			cin >> t;
			
			if ((t - tmp)%2)
				good = false;
		}
		
		cout << (good ? "YES" : "NO") << endl;
	}
}