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

int main()
{
    yccc;
    
    int m, n, w, c = 1;
    while (cin >> m >> n >> w) {
        if (m == 0) break;
        
        ll ans = 0, wall = 0;
        
        vec<vec<p<int>>> _list(m);
        for (int i = 0; i < w; ++i) {
            int r, s, e;
            cin >> s >> r >> e >> r;
            
            _list[r].eb(s, e);
            wall += e-s+1;
        }
        for (int i = m-1; i >= 0; --i) {
            // devec(_list[i]);
        }
        
        for (int i = m-1; i >= 0; --i) {
            sort(al(_list[i]));
            
            if (i == m-1) {
                for (auto &k : _list[i])
                    k.F = 0;
            } else {
                for (auto r : _list[i+1]) {
                    for (auto &s : _list[i]) {
                        if (r.S >= s.F-1)
                            s.F = min(s.F, r.F);
                    }
                    
                    if (r.S == n-1)
                        _list[i].eb(r.F, r.S);
                }
            }
            
            if (!_list[i].empty()) {
                vec<p<int>> next = {_list[i][0]};
                for (auto k : _list[i]) {
                    if (k.F <= next.back().S+1)
                        next.back().S = max(next.back().S, k.S);
                    else
                        next.eb(k.F, k.S);
                }
                _list[i] = next;
            }
            
            // devec(_list[i]);
            for (auto k : _list[i])
                ans += k.S-k.F+1;
        }
        
        // cout << ans << ' ' << wall << endl;
        cout << "Case " << c++ << ": " << ans - wall << endl;
    }
}