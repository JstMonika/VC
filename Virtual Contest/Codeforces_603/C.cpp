#include <bits/stdc++.h>
using namespace std;

int ans[10000000];

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n;
		cin >> n;
		
		int tmp = n, cont = 0;
		int s = 1;
		while (tmp != 0)
		{
			if (n/tmp > n%tmp)
			{
				ans[cont] = n/tmp;
				
				tmp = n / (ans[cont]+1);
				
				cont++;
			}
			
			s++;
		}
		
		cout << cont+1 << endl << 0;
		for (int i = 0; i < cont; i++)
			cout << ' ' << ans[i];
		
		cout << endl;
	}
}