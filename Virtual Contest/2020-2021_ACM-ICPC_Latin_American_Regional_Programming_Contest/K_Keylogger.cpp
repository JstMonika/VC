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
const int MOD = 1e9+7;
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

int main()
{
    yccc;
    
    ll k, l;
    cin >> k >> l;
    
    vec<vec<ll>> _list(k, vec<ll>(k));
    for (auto &i : _list)
        for (auto &k : i)
            cin >> k;
            
    int n;
    cin >> n;
    vec<ll> passwd(n-1);
    for (auto &i : passwd)
        cin >> i;
    
    vec<vec<ll>> dp(n, vec<ll>(k));
    for (int i = n-1; i >= 0; i--) {
        for (int pk = 0; pk < k; pk++) {
            if (i == n-1) dp[i][pk] = pk+1;
            else {
                if (pk) dp[i][pk] = dp[i][pk-1];
                
                ll lower = distance(_list[pk].begin(), lower_bound(al(_list[pk]), passwd[i] - l));
                lower = (lower ? dp[i+1][lower-1] : 0);
                
                ll upper = distance(_list[pk].begin(), upper_bound(al(_list[pk]), passwd[i] + l));
                upper = (upper ? dp[i+1][upper-1] : 0);
                
                // cout << upper << ' ' << lower << endl;
                (dp[i][pk] += (upper - lower + MOD)) %= MOD;
            }
        }
    }
    
    // devec2(dp);
    
    cout << dp[0][k-1];
}