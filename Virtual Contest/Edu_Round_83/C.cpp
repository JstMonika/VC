#include <bits/stdc++.h>
using namespace std;

const long long limit = 10000000000000000;

long long power[70];

int create(int);

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		bool good = true;
		
		int n, k;
		cin >> n >> k;
		
		int rear = create(k);
		
		vector<bool> _list(100);
		
		long long tmp;
		for (int i = 0; i < n; i++)
		{
			cin >> tmp;
			
			for (int m = rear; m >= 0; m--)
			{
				// cout << tmp << ' ' << power[m] << endl;
				if (tmp >= power[m])
				{
					// cout << "hi" << endl;
					if (_list[m])
					{
						// cout << m << endl;
						good = false;
					}
					
					_list[m] = true;
					tmp -= power[m];
				}
			}
			
			if (tmp)
				good = false;
		}
		
		
		cout << (good ? "YES" : "NO") << endl;
	}
}

int create(int k)
{
	long long cur = 1;
	int i = 0;
	while (cur <= limit)
	{
		// cout << cur << endl;
		power[i] = cur;
		cur *= k;
		
		i++;
	}
	
	return i-1;
}