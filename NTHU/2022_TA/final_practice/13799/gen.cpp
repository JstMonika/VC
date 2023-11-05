#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

mt19937 r(chrono::steady_clock::now().time_since_epoch().count());

int main() {
    yccc;
    
    int n = r() % 100000 + 1, k = 20000;
    vec<int> _list(n), count(k+1);
    
    cout << n << ' ' << k << endl;
    for (int i = 0; i < n; i++) {
        if (i < k) {
            do {
                _list[i] = r() % k + 1;
            } while (count[_list[i]]);
            
            count[_list[i]] = true;
        } else {
            _list[i] = _list[i-k];
        }
    }
    
    int times = 3;
    for (int i = 0; i < times; i++) {
        _list[r() % n] = r() % k + 1;
    }
    
    for (int i = 0; i < n; i++)
        cout << _list[i] << " \n"[i == n-1];
}