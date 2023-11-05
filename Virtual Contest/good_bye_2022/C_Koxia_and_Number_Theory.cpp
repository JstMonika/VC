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

vec<bool> prime(10000001);

int main() {
    yccc;
    
    int t;
    cin >> t;
    
    int N = 10000000;
    for (int i = 2; i * i <= N; i++) {
        if (prime[i]) continue;
        
        for (int k = i * i; k <= N; k += i) {
            prime[k] = true;
        }
    }
    
    
    vec<int> p_list;
    for (int i = 2; i <= N; i++)
        if (!prime[i]) p_list.eb(i);
    
    // cout << p_list.size();
    
    while (t--) {
        int n;
        cin >> n;
        
        vec<int> _list(n);
        for (auto &i : _list) {
            cin >> i;
        }
        
        bool G = false;
        for (auto i : p_list) {
            unordered_set<int> _set;
            bool good = true;
            
            for (int k = 0; k < n; k++) {
                if (_set.count(_list[k] % i)) {
                    good = false;
                    break;
                }
                
                _set.emplace(_list[k] % i);
            }
            
            if (good) {
                G = true;
                break;
            }
        }
        
        if (G) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
}