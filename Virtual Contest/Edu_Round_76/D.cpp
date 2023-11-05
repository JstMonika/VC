#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

bool cmp(const pair<int, int> &a, const pair<int, int> &b)
{
	if (a.first != b.first)
		return (a.first < b.first);
	
	return (a.second > b.second);
}

int main()
{
	int c;
	cin >> c;
	
	while (c--)
	{
		int n_mons;
		cin >> n_mons;
		
		vector<int> monster(n_mons);
		for (auto &tmp : monster)
			cin >> tmp;
		
		// for (auto &tmp : monster)
			// cout << tmp << endl;
		// cout << monster.size() << endl;
		
		int n_heroes;
		cin >> n_heroes;
		
		vector<pii> hero(n_heroes);
		for (auto &tmp : hero)
			cin >> tmp.second >> tmp.first;
		
		sort(hero.begin(), hero.end(), cmp);
		
		// for (auto &tmp : hero)
			// cout << tmp.second << ' ' << tmp.first << endl;
		// cout << hero.size() << endl;
		
		vector<int> max_power(n_mons+2, 0);
		for (int i = n_mons; i >= 1; i--)
		{
			auto it = lower_bound(hero.begin(), hero.end(), make_pair(i, numeric_limits<int>::min()));
			
			if (it != hero.end())
				max_power[i] = max((it->second), max_power[i+1]);
		}
		
		/* 
		cout << '-' << endl;
		for (auto t : max_power)
			cout << t << endl;
		cout << '-' << endl;
		 */

		int conquer = 0, count = 0;
		while (++count)
		{
			int i = 1, cur_max = -1;
			if (monster[conquer] > max_power[i])
			{
				// cout << monster[conquer] << ' ' << max_power[i] << endl;
				// cout << conquer << ' ' << i << endl;
				// cout << count << endl;
				
				cout << "-1" << endl;
				break;
			}
			
			while (max(cur_max, monster[conquer]) <= max_power[i] and conquer < n_mons)
			{
				cur_max = max(cur_max, monster[conquer]);
				i++;
				conquer++;
			}
			
			// cout << "conquer = " << conquer << endl;
			if (conquer == n_mons)
			{
				cout << count << endl;
				break;
			}
		}
	}
}