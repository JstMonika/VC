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
        int a, b;
        cin >> a >> b;
        
        if (a < b) swap(a, b);
        
        if (__gcd(a, b) != 1) {
            cout << 0 << endl;
            continue;
        }
        
        int sub = a-b, sum = a+b;
        // cout << sub << ' ' << sum << endl;
        
        vec<int> g;
        for (int i = 2; i * i <= sub; i++) {
            if (sub % i == 0) {
                g.eb(i);
                while (sub % i == 0) sub /= i;
            }
        }
        
        if (sub != 1) g.eb(sub);
        
        // for (auto i : g) cout << i << ' ';
        // cout << endl;
        
        if (g.size() == 0) {
            cout << -1 << endl;
        } else {
            int ans = 1e9;
            bool good = true;
            
            for (auto i : g) {
                int mod = (a+b) % i;
                mod = i - mod;
                
                if (mod & 1) mod += i;
                if (mod & 1) good = false;
                
                ans = min(ans, mod / 2);
                // cout << i << ' ' << mod/2 << endl;
            }
            
            
            
            cout << (good ? ans : -1) << endl;
        }
    }
}