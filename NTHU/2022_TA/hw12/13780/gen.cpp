#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

mt19937 r(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    yccc;

	int n = r() % 1000 + 1, x = r() % 700, d = r() % 90 + 10;

	cout << n << ' ' << x << ' ' << d << endl;
	
	for (int i = 0; i < n; i++) {
		cout << r() % 10 + 1 << " \n"[i == n-1];
	}

	vec<bool> vis(n+1);
	vis[1] = true;

	vec<p<int>> ans;
	for (int i = 0; i < n-1; i++) {
		int root;
		do {
			root = r() % n + 1;
		} while (!vis[root]);

		int go;
		do {
			go = r() % n + 1;
		} while (vis[go]);

		if (r() % 2) {
			ans.eb(root, go);
		} else {
			ans.eb(go, root);
		}

		vis[go] = true;
	}
    
    shuffle(al(ans), default_random_engine{});

	for (auto &i : ans) {
		cout << i.F << ' ' << i.S << endl;
	}
}
