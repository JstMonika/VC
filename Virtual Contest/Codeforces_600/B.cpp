#include <bits/stdc++.h>
using namespace std;

vector<int> event, cont;

int main()
{
	int n;
	cin >> n;
	
	
	event.resize(n);
	for (int i = 0; i < n; i++)
		cin >> event[i];
	
	map<int, int> stay;
	int days = 0, num = 0, cur = 0;
	
	bool good = true;
	for (int i = 0; i < n; i++)
	{
		if (event[i] < 0)
		{
			if (stay.count(event[i] * (-1)) and stay[event[i]*(-1)] == 1)
			{
				stay[event[i]*(-1)] = -1;
				num--;
			}
			else
			{
				good = false;
				break;
			}
		}
		
		else
		{
			if (stay.count(event[i]))
			{
				good = false;
				break;
			}
			else
			{
				stay[event[i]] = 1;
				num++;
			}
		}
		
		if (!num)
		{
			days++;
			cont.push_back(i - cur + 1);
			cur = i+1;
			stay.clear();
		}
	}
	
	if (!stay.empty())
		good = false;
	
	if (good)
	{
		cout << days << endl;
		cout << cont[0];
		for (int i = 1; i < days; i++)
			cout << ' ' << cont[i];
		
		cout << endl;
	}
	else
		cout << -1 << endl;
}