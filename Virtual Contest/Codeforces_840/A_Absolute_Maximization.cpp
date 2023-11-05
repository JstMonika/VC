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
        int n;
        cin >> n;
        
        vec<int> _list(n);
        for (auto &i : _list) {
            cin >> i;
        }
        
        vec<int> count(10);
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 10; k++) {
                if (_list[i] & (1<<k)) {
                    count[k]++;
                }
            }
        }
        
        int ans = 0;
        for (int i = 0; i < 10; i++) {
            if (count[i] != 0 and count[i] != n) {
                ans += (1<<i);
            }
        }
        
        cout << ans << endl;
    }
}