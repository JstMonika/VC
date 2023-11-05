#include <bits/stdc++.h>
using namespace std;
int s, e;
int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int cont = 0;
		cin >> s >> e;
		
		if (s < e)
		{
			if (e-s >= 5)
				cont += (e-s) / 5;
				
				
				switch ((e-s) - cont*5)
				{
					case 4:
					case 3:
						cont += 2;
						break;
					case 2:
					case 1:
						cont++;
						break;
				}
		}
		
		else
		{
			if (s-e >= 5)
				cont += (s-e) / 5;
			
			switch ((s-e) - cont*5)
				{
					case 4:
					case 3:
						cont += 2;
						break;
					case 2:
					case 1:
						cont++;
						break;
				}
		}
		cout << cont << endl;
	}
}