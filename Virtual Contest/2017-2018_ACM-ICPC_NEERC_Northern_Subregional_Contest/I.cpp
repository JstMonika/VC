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
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-6) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

bool check(ll n) {
    while (n % 2 == 0) n /= 2;
    
    return (n == 1);
}

int main()
{
    yccc;
    
    ll n;
    
    freopen("little.in", "r", stdin);
    freopen("little.out", "w", stdout);
    
    cin >> n;
    
    vec<vec<ll>> ans;
    
    if (check(n)) {
        cout << -1;
        return 0;
    }
    
    ans.eb(vec<ll>({n}));
    
    ll _sqrt = ll(sqrt(n) + eps);
    
    if (_sqrt * _sqrt == n) {
        ans.eb(vec<ll>({_sqrt, _sqrt}));
    } else if (_sqrt * (_sqrt+1) == n) {
        ans.eb(vec<ll>({_sqrt, _sqrt+1}));
    } else if ((_sqrt+1) * (_sqrt+1) == n) {
        ans.eb(vec<ll>({_sqrt+1, _sqrt+1}));
    }
    
    for (ll i = 2; i <= 1000000; i++) {
        vec<ll> tmp;
        ll _n = n;
        
        while (_n % i == 0) {
            tmp.eb(i);
            _n /= i;
        }
        
        if (tmp.empty()) continue;
        
        while (_n % (i+1) == 0) {
            tmp.eb(i+1);
            _n /= (i+1);
        }
        
        if (_n == 1 and tmp.size() >= 3) {
            ans.eb(tmp);
        }
    }
    
    cout << ans.size() << endl;
    for (auto i : ans) {
        cout << i.size();
        for (auto k : i) {
            cout << ' ' << k;
        }
        cout << endl;
    }
}