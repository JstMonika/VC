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
        int ans = 1e9;
        int n, _m;
        cin >> n >> _m;
        
        vec<p<int>> _list(n);
        int c = 0;
        for (auto &i : _list) {
            cin >> i.F;
            i.S = c++;
        }
        
        int l = 0, r = n;
        while (l <= r) {
            int m = (l + r) / 2;
            
            auto cmp = [m](p<int>& a, p<int>& b) {
                if (a.F != b.F) return a.F < b.F;
                if (a.S == m) return a.F < b.F;
                return b.F < a.F;
            };
            
            sort(al(_list), cmp);
            
            int sum = 0, dk = 0;
            for (int i = 0; i < m; i++) {
                sum += _list[i].F;
                if (_list[i].S == m) dk = 1;
            }
            
            if (sum > _m) {
                r = m-1;
            } else {
                int count = 0;
                for (int i = 0; i < n; i++) {
                    if (i < m) {
                        count += (m < _list[i].S);
                    } else {
                        count += (m < _list[i].S + 1);
                    }
                }
                
                ans = min(count + 1, ans);
                l = m+1;
            }
        }
        
        cout << ans << endl;
    }
}