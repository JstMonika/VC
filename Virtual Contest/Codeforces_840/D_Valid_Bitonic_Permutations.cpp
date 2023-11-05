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

const int MOD = 1e9 + 7;
const int MAX = 5000;
ll fact[MAX], tcaf[MAX];

ll binpow(ll x, ll d) {
    if (d < 0) d += MOD-1;
    
    ll y = 1;
    do {
        if (d & 1) (y *= x) %= MOD;
        (x *= x) %= MOD;
    } while (d >>= 1);
    
    return y;
}

void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = i * fact[i-1] % MOD;
    }
    for (int i = n; i >= 0; i--) {
        tcaf[i] = binpow(fact[i], -1);
    }
}

ll nCr(int n, int r) {
    if (n < 0) return 0;
    if (r < 0 || r > n) return 0;
    return fact[n] * tcaf[r] % MOD * tcaf[n-r] % MOD;
}

int main() {
    yccc;
    
    init(500);
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, i, j, x, y;
        cin >> n >> i >> j >> x >> y;
        
        ll sum = 0, tmp;
        if (x > y) {
            i = n+1 - i;
            j = n+1 - j;
            
            swap(x, y);
            swap(i, j);
        }
        
        // cout << i << ' ' << j << ' ' << x << ' ' << y << endl;
        
        if (y != n) {
            for (int z = 0; z <= j-i-2; z++) {
                cout << "C(" << n-y-1 << ", " << z << ") * C(" << n-x-2-z << ", " << j-i-2-z-max(0, n-y-1-z) << ") = " << nCr(n-y-1, z) * nCr(n-x-2-z, j-i-2-z-max(0, n-y-1-z)) << endl;
                (sum += nCr(n-y-1, z) * nCr(n-x-2-z, j-i-2-z-max(0, n-y-1-z)) % MOD) %= MOD;
            }
            
            (sum *= nCr(x-1, i-1)) %= MOD;
        }
        
        // cout << "test\n";
        // cout << x-1 << ' ' << i-1 << ' ' << y-x-1 << ' ' << j-i-1 << endl;
        // cout << nCr(x-1, i-1) << ' ' << nCr(y-x-1, j-i-1) << endl;
        
        if (y != n) {
            for (int z = 0; z <= n-j-1; z++) {
                (tmp += nCr(n-y-1, z)) %= MOD;
            }
        } else tmp = 1;
        
        (tmp *= nCr(x-1, i-1) * nCr(y-x-1, j-i-1) % MOD) %= MOD;
        
        cout << sum << ' ' << tmp << endl;
        (sum += tmp) %= MOD;
        cout << sum << endl;
        
    }
}