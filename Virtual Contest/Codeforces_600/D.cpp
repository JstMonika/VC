#include <bits/stdc++.h>
using namespace std;

bool done[200001];
vector<int> adj[200001];

void dfs(int node, int& weaker, int& bigger)
{
	if (!done[node])
	{
		done[node] = true;
		
		weaker = min(weaker, node);
		bigger = max(bigger, node);
		
		// cout << adj[node].size() << endl;
		for (auto neighbor : adj[node])
			dfs(neighbor, weaker, bigger);
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m;
	cin >> n >> m;
	
	while (m--)
	{
		int u, v;
		cin >> u >> v;
		
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	vector< pair<int, int> > group;
	for (int i = 0; i < n; i++)
	{
		if (!done[i])
		{
			int weaker = i;
			int bigger = i;
			
			dfs(i, weaker, bigger);
			
			group.emplace_back(weaker, bigger);
		}
	}
	
	int count = 0;
	int curMAX = -1;
	
	for (auto cur : group)
	{
		// cout << cur.first << ' ' << cur.second << endl;
		if (cur.first <= curMAX)
			count++;
		
		curMAX = max(curMAX, cur.second);
	}
	
	cout << count << endl;
}