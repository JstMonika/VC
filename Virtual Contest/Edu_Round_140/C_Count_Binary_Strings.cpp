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

const int MOD = 998244353;

int main() {
    yccc;
    
    int n;
    cin >> n;
    
    vec<vec<int>> _list(n, vec<int>(n));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n-i; k++) {
            cin >> _list[i][k];
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (_list[i][0] != 1) {
            cout << 0;
            return 0;
        }
    }
    
    for (int i = 1; i < n; i++) {
        for (int k = 0; k < n-i; k++) {
            if (_list[k][i] == 1 and _list[k][i-1] == 2) {
                cout << 0;
                return 0;
            } else if (_list[k][i] == 1 and _list[k+1][i-1] == 2) {
                cout << 0;
                return 0;
            }
        }
    }
    
    ll ans = 2;
    for (int i = 1; i < n-1; i++) {
        ans *= 
    }   
}