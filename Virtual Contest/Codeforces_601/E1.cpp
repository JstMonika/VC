#include <bits/stdc++.h>
using namespace std;

int main()
{
	int n;
	cin >> n;
	
	long long sum = 0;
	
	vector<int> box(n);
	for (int i = 0; i < n; i++)
	{
		cin >> box[i];
		sum += box[i];
	}
	
	int i = 2;
	while (sum % i) i++;
	
	for (int i = 0; i < n; i++)
	{
		
	}
}