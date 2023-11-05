#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

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

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const ll MOD = 998244353;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

ll tmod(ll a, ll n) {
    ll ret = 0;
    do {
        if (n % 2) (ret += a) %= MOD;
        (a += a) %= MOD;
    } while (n >>= 1);
    
    return ret;
}

ll power(ll a, ll n) {
    ll ret = 1;
    do {
        if (n % 2) (ret *= a) %= MOD;
        (a *= a) %= MOD;
    } while (n >>= 1);
    
    return ret;
}

bool isprime(ll i) {
    for (ll k = 2; k * k <= i; k++) {
        if (i % k == 0) return false;
    }
    
    return true;
}

int main()
{
    yccc;
    
    ll n, m;
    cin >> n >> m;
    
    ll total = tmod(m, m), ans = 0;
    // cout << total << endl;
    
    bool stop = false;
    ll now = 1, sub = m;
    for (ll i = 2; i <= n; i++) {
        if (isprime(i) and now <= m)
            now *= i;
        
        if (now > m) {
            sub = 0;
        } else if (!stop)
            sub = tmod(sub, m / now % MOD);
                        
        (ans += (total - sub + MOD) % MOD) %= MOD;
        total = tmod(total, m);
    }
    
    cout << ans % MOD << endl;
}