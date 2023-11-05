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
        
        if (k == 1) {
            for (int i = 1; i <= n; i++) {
                cout << i << " \n"[i == n];
            }
            
            continue;
        }
        
        vec<int> _list(n);
        int r = n, l = 1;
        for (int i = 0; i < n; i += k-1) {
            for (int z = 0; z < k-1; z++) {
                if (i + z >= n) break;
                
                if ((i / (k-1)) & 1) {
                    _list[i+z] = l++;
                } else _list[i+z] = r--;
            }
            
            // cout << i << endl << flush;
        }
        
        for (int i = 0; i < n; i++) {
            cout << _list[i] << " \n"[i == n-1];
        }
    }
}