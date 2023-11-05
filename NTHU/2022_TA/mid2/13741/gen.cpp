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
	
    int n = r() % 10 + 1, m = r() % 10 + 1, K = 3;
    vec<vec<char>> _list(n, vec<char>(m));
    
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            _list[i][k] = (r() & 1 ? '1' : '0');
        }
    }
    
    _list[r() % n][r() % m] = 'x';
    cout << n << ' ' << m << ' ' << K << endl;
    
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            cout << _list[i][k];
        }
        cout << endl;
    }
}
