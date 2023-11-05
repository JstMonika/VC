#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const ll MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n, k;
vec<int> _list;
vec<ll> fact(1010), tcaf(1010);

ll deg(ll x, ll d) {
    if (d < 0) d += MOD - 1;
    
    ll y = 1;
    while (d) {
        if (d & 1) (y *= x) %= MOD;
        d /= 2;
        (x *= x) %= MOD;
    }
    
    return y;
}

void init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) {
        fact[i] = i * fact[i-1] % MOD;
    }
    for (int i = n; i >= 0; --i)
        tcaf[i] = deg(fact[i], -1);
}

ll nCr(int n, int r) {
    if (r < 0 or r > n) return 0;
    // cout << "---" << n << ' ' << r << endl;
    // cout << fact[n] << ' ' << endl;
    // cout << tcaf[r] << endl;
    return fact[n] * tcaf[r] % MOD * tcaf[n-r] % MOD;
}

ll nHr(int n, int r) {
    return nCr(n+r-1, r);
}

ll G(int i) {
    ll ret = 1;
    
    for (auto z : _list) {
        // cout << i << ' ' << z << ' ' << nHr(i, z) << endl;
        (ret *= nHr(i, z)) %= MOD;
    }
    
    return ret;
}

int main()
{
    yccc;
    
    cout << deg(2, 2) << endl;
    
    int c;
    cin >> c;
    
    init(1005);
    
    // cout << deg(2, 5) << endl;
    // cout << nCr(3, 1) << ' ' << nCr(3, 2) << ' ' << endl;
    
    while (c--) {
        cin >> n >> k;
        
        map<int, int> _map;
        while (n--) {
            int num;
            cin >> num;
            _map[num]++;
        }
        _list.clear();
        for (auto i : _map) _list.eb(i.S);
        
        // devec(_list);
        
        vec<ll> dp(k+1);
        dp[1] = 1;
        for (int i = 2; i <= k; i++) {
            for (int z = 1; z < i; z++) {
                (dp[i] -= dp[z] * nCr(i, i-z)) %= MOD;
            }
            
            // debug(dp[i]);
            
            (dp[i] += G(i) + MOD) %= MOD;
            
            
            // debug(G(i));
        }
        
        cout << dp[k] << endl;
    }
}