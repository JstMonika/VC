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

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int r(int s, int e) {
    return rnd() % (e-s+1) + s;
}

int main() {
    yccc;
	
    int n = r(1, 50), s = r(15, 30);
	cout << n << ' ' << s << endl;
	
	for (int i = 0; i < n; i++) {
		cout << r(0, 10) << " \n"[i == n-1];
	}
}
