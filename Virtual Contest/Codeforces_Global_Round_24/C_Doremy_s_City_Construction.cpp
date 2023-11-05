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

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vec<int> _list(n);
        for (auto &i : _list) {
            cin >> i;
        }
        
        sort(al(_list));
        
        vec<p<int>> count;
        count.eb(_list[0], 1);
        
        for (int i = 1; i < n; i++) {
            if (_list[i] != count.back().F) {
                count.eb(_list[i], 1);
            } else {
                count.back().S++;
            }
        }
        
        n = count.size();
        vec<ll> pre(n+1);
        
        for (int i = 1; i <= n; i++) {
            pre[i] = pre[i-1] + count[i-1].S;
        }
        
        if (n == 1) {
            cout << pre[1] / 2 << endl;
        } else {
            ll ans = 0;
            for (int i = 1; i <= n; i++) {
                ans = max((pre[i] - pre[0]) * (pre[n] - pre[i]), ans);
            }
            
            cout << ans << endl;
        }
    }
}