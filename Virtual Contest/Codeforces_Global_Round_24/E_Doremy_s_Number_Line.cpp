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
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, k;
        cin >> n >> k;
        
        // cout << n << ' ' << k << endl;
        
        p<int> goal;
        cin >> goal.F >> goal.S;
        
        if (n == 1) {
            cout << (k <= goal.F ? "YES\n" : "NO\n");
            continue;
        }
        
        vec<p<int>> _list(n-1);
        for (auto &i : _list)
            cin >> i.F >> i.S;
         
        auto cmp = [](p<int>& a, p<int>& b) -> bool {
            if (a.F > b.F) return a.F > b.F;
            return a.S < b.S;
        };
        sort(al(_list), cmp);
        
        int _max = _list[0].F;
        if (_list[0].F == k) _max--;
        
        for (int i = 1; i < n-1; i++) {
            int _min = min(_max, _list[i].F);
            
            _max = max(_max, _min + _list[i].S);
            
            if (_max == k) _max--;
        }
        
        if (k <= goal.F or k <= min(_max, goal.F) + goal.S) cout << "YES\n";
        else cout << "NO\n";
    }
}