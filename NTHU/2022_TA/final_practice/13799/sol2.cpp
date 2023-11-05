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
    
    int n, k, ans = 0;
    cin >> n >> k;
    
    vec<int> _list(n);
    for (auto &i : _list)
        cin >> i;
        
    for (int i = 0; i < n-k+1; i++) {
        set<int> _set;
        for (int z = 0; z < k; z++) {
            _set.emplace(_list[i+z]);
        }
        
        if (_set.size() == k) ans++;
    }
    
    cout << ans;
}