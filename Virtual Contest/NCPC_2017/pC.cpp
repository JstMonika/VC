#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;

const int maxn = 1e5 + 5;
int n;
struct Card {
	int c[3], id;
}a[maxn];
struct node {
	int val, id;
	bool operator < (const node &rhs) const {
		if (val != rhs.val)	return val < rhs.val;
		return id > rhs.id;
	}
};
set<int> s[3][360];
set<node> S;
map<int, int> mp;
int V[maxn];

int getval(int i) {
	int sum = 0;
	for (int j = 0; j < 3; j++) {
		int cur = a[i].c[j];
		if (s[j][cur].size() >= 2)	continue;
		int l = cur;
		do {
			l = (l - 1 + 360) % 360;
		} while (s[j][l].size() == 0);
		int r = cur;
		do {
			r = (r + 1) % 360;
		} while (s[j][r].size() == 0);
		if (l > cur)	l -= 360;
		if (r < cur)	r += 360;
		sum += r - l;
	}
	return sum;
}

void deal(int j, int pos) {
	if (s[j][pos].size() >= 2)	return;
	int id = *s[j][pos].begin();
	int val = getval(mp[id]);
	S.erase({V[mp[id]], id});
	S.insert({V[mp[id]] = val, id});
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &a[i].c[j]);
		}
		scanf("%d", &a[i].id);
		int id = a[i].id;
		mp[id] = i;
		for (int j = 0; j < 3; j++) {
			s[j][a[i].c[j]].insert(id);
		}
	}
	for (int i = 0; i < n; i++) {
		V[i] = getval(i);
		S.insert({V[i], a[i].id});
	}
	while (n--) {
		int id = S.begin()->id;
		printf("%d\n", id);
		S.erase(S.begin());
		int t = mp[id];
		for (int j = 0; j < 3; j++) {
			int k = a[t].c[j];
			if (s[j][k].size() >= 2) {
				s[j][k].erase(s[j][k].find(id));
				int iid = *s[j][k].begin(), vval = getval(mp[iid]);
				S.erase({V[mp[iid]], iid});
				S.insert({V[mp[iid]] = vval, iid});
			} else if (n >= 1) {
				s[j][k].erase(s[j][k].begin());
				int l = k;
				do {
					l = (l - 1 + 360) % 360;
				} while (s[j][l].size() == 0);
				deal(j, l);
				int r = k;
				do {
					r = (r + 1) % 360;
				} while (s[j][r].size() == 0);
				deal(j, r);
			}
		}
	}
}