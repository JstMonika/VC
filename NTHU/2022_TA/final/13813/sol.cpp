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

int main() {
    yccc;
    
    int n, K;
    cin >> n >> K;
    
    ll ans = 0;
    vec<int> _list(n);
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < K; k++) {
            int t;
            cin >> t;
            
            if (t)
                _list[i] |= (1<<k);
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int k = i+1; k < n; k++) {
            if (_list[i] == _list[k])
                ans++;
        }
    }
    
    cout << ans << endl;
}