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

int n, INF = 1e9;
vec<int> _list;

void solve(int l, int r) {
    if (l < 0 or r >= n) return;
    if (l > r) return;
    
    int _min = INF, _max = -1;
    int lidx, ridx;
    
    for (int i = l; i <= r; i++) {
        if (_list[i] >_min)
    }
}

int main() {
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        cin >> n;
        
        _list.resize(n);
        for (auto &i : _list)
            cin >> i;
            
        solve(0, n-1);
        
        ll sum = 0;
        for (auto i : _list)
            sum += i;
            
        cout << sum << endl;
    }
}