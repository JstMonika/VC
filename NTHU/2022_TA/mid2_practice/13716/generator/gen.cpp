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

mt19937 r(chrono::system_clock::now().time_since_epoch().count());

int main() {
    yccc;
	
	int n = r() % 20 + 1, m = r() % 20 + 1, q = r() % 3 + 1;
	cout << n << ' ' << m << ' ' << q << endl;

	vec<vec<char>> _list(n, vec<char>(m));

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < m; k++) {
			int t = r() % 15;

			if (t <= 9) _list[i][k] = '.';
			else _list[i][k] = 'X';
		}
	}

	_list[r() % n][r() % m] = '-';
	for (auto &i : _list) {
		for (auto &k : i) {
			cout << k;
		}

		cout << endl;
	}

	for (int i = 0; i < q+1; i++) {
		cout << r() % n << ' ' << r() % m << endl;
	}
}
