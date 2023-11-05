#include <bits/stdc++.h>
using namespace std;

#define REP(i, a, b) \
for (int i = a; i < b; i++)

vector<int> pset(1000);
int size = 1000;
void initSet(int n) { pset.resize(n); REP(i, 0, n) pset[i] = i; size = n; }
int findSet(int i) { return (pset[i] == i) ? i : pset[i] = findSet(pset[i]); }
bool isSameSet(int i, int k) { return (findSet(i) == findSet(k)); }
void unionSet(int i, int k)
{
	if (!isSameSet(i, k))
		size--;
	
	pset[findSet(i)] = findSet(k);
}

int main()
{
	int n;
	cin >> n;
	
	initSet(n);
	
	vector< vector<int> > pw(26);
	
	string tmp;
	for (int i = 0; i < n; i++)
	{
		cin >> tmp;
		for (int k = 0; k < tmp.size(); k++)
		{
			pw[tmp[k] - 'a'].push_back(i);
			
			if (pw[tmp[k] - 'a'].size() != 1)
				unionSet(i, pw[tmp[k]-'a'][0]);
		}
	}
	
	cout << size;
}