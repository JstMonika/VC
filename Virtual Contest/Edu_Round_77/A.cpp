#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	int test[10001];
	for (int i = 1; i <= 10000; i++)
		test[i] = i*i;
	
	while (c--)
	{
		int k, sum;
		cin >> k >> sum;
		
		int count = sum % k;
		int base = sum / k;
		
		long long ans = (sum % k) * test[base+1] + (k - sum%k) * test[base];
		
		cout << ans << endl;
	}
}