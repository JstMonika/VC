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
		// cout << "n = " << n << endl;
		
		vector<bool> done(n+1);
		vector<int> ans;
		
		int curmax = 0, mini = 1;
		bool good = true;
		for (int i = 0; i < n; i++)
		{
			int tmp;
			cin >> tmp;
			
			if (tmp > curmax)
			{
				ans.push_back(tmp);
				done[tmp] = true;
				
				if (tmp == mini)
					mini++;
				
				curmax = max(tmp, curmax);
			}
			else
			{
				if (mini > tmp)
				{
					good = false;
				}
				else
				{
					ans.push_back(mini);
					done[mini] = true;
					
					while (done[++mini]) ;
				}
			}
			
		}
		
		if (good)
		{
			for (int i = 0; i < n; i++)
				if (!i)
					cout << ans[i];
				else
					cout << ' ' << ans[i];
				
			cout << endl;
		}
		else
			cout << -1 << endl;
	}
}