#include <bits/stdc++.h>
using namespace std;

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int ans = -1;
		
		int n;
		cin >> n;
		
		map<int, int> dis;
		while (n--)
		{
			int tmp;
			cin >> tmp;
			
			if (!dis.count(tmp))
				dis[tmp] = n;
			else
			{
				dis[tmp] = dis[tmp] - n + 1;
				
				if (ans == -1)
					ans = dis[tmp];
				else
					ans = min(dis[tmp], ans);
				
				dis[tmp] = n;
			}
		}
		
		cout << ans << endl;
	}
}