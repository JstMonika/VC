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
        int n, m, k;
        cin >> n >> m >> k;
        
        vec<int> _list(m);
        for (auto &i : _list)
            cin >> i;
            
        sort(al(_list), greater<int>());
        
        int count = n / k + (n % k != 0);
        if (_list[0] > count) cout << "NO\n";
        else {
            int c = 0;
            for (int i = 0; i < m; i++) {
                if (_list[i] == count) c++;
            }
            
            if (c > (n % k ? n % k : k)) cout << "NO\n";
            else cout << "YES\n";
        }
    }
}