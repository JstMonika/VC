#include <bits/stdc++.h>
using namespace std;
bool first = true;

int main()
{
	int n, m;
	cin >> n >> m;
	
	vector<int> cake(n);
	for (int i = 0; i < n; i++)
		cin >> cake[i];
	
	sort(cake.begin(), cake.end());
	
	long long store[m] = {0};
	
	long long sum = 0, count = 0;
	for (int i = 0; i < n; i++)
	{
		sum += store[i%m];
		store[i%m] += cake[i];
		
		sum += cake[i];
		count++;
		
		if (!i)
			cout << sum;
		else
			cout << ' ' << sum;
	}
	cout << endl;
}