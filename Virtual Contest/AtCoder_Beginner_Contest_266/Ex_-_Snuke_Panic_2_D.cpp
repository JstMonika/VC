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

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-6) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

struct Item {
    ll t, x, y, v;
    
    Item() {};
    Item(ll t, ll x, ll y, ll v) : t(t), x(x), y(y), v(v) {}
    
    bool operator<(Item i) {
        if (t != i.t)
            return t < i.t;
        return y < i.y;
    }
};

vec<vec<ll>> dp(100001, vec<ll>(5));
int main()
{
    yccc;
    
    int n;
    cin >> n;
    vec<Item> _list;
    vec<int> time;
    
    for (int i = 0; i < n; i++) {
        ll t, x, y, v;
        cin >> t >> x >> y >> v;
        
        if (x+y > t) continue;
        else {
            _list.eb(t, x, y, v);
            time.eb(t);
        }
    }
    
    sort(al(_list));
    sort(al(time));
    time.resize(distance(time.begin(), unique(al(time))));
    
    vec<map<int, ll>> dp(time.size());
    for (int i = 0; i < _list.size(); i++) {
        int idx = lower_bound(al(time), _list[i].t) - time.begin();
        dp[idx][i] = _list[i].v;
    }
    
    for (int i = 1; i < time.size(); i++) {
        for (auto& now : dp[i]) {
            ll _max = 0;
            
                for (auto k : dp[z]) {
                    if (_list[k.F].y > _list[now.F].y) break;
                    
                    if (abs(_list[now.F].x - _list[k.F].x) + abs(_list[now.F].y - _list[k.F].y) <= abs(_list[now.F].t - _list[k.F].t))
                        _max = max(_max, k.S);
                }
            }
            
            now.S += _max;
        }
    }
    
    ll ans = 0;
    for (auto i : dp.back())
        ans = max(ans, i.S);
    cout << ans;
    
    // for (auto i : dp) {
    //     for (auto k : i)
    //         cout << _list[k.F].x << ' ' << _list[k.F].y << ": " << k.S << endl;
        
    //     cout << "--------\n";
    // }
    
    // for (int i = 0; i < 6; i++) {
    //     for (int k = 0; k < 5; k++)
    //         cout << dp[i][k] << ' ';
    //     cout << endl;
    // }
}