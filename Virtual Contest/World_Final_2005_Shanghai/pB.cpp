#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

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
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

vec<p<double>> BTS;
p<double> ret;

double dis(p<double> a, p<double> b) {
    double dx = a.F - b.F, dy = a.S - b.S;

    return sqrt(dx * dx + dy * dy);
}

int find_idx(p<double> src) {
    double idx = -1, _max = INF;
    for (int i = 0; i < BTS.size(); i++) {
        if (dis(src, BTS[i]) < _max) {
            _max = dis(src, BTS[i]);
            idx = i;
        }
    }

    return idx;
}

int find_idx(p<double> sp, p<double> ep, double d) {
    double rad = atan2(ep.S - sp.S, ep.F - sp.F);
    
    ret = make_pair(d * cos(rad) + sp.F, d * sin(rad) + sp.S);

    double idx = -1, _max = INF;
    for (int i = 0; i < BTS.size(); i++) {
        if (dis(ret, BTS[i]) < _max) {
            _max = dis(ret, BTS[i]);
            idx = i;
        }
    }

    return idx;
}

int main()
{
    yccc;
    
    int T = 1;
    int b, c, r, q;
    while (cin >> b >> c >> r >> q) {
        if (!b)
            break;
            
        cout << "Case " << T++ << ":\n";

        BTS.resize(b);
        for (auto &i : BTS)
            cin >> i.F >> i.S;
        
        vec<p<double>> city(c);
        vec<int> tower(c);
        for (auto &i : city)
            cin >> i.F >> i.S;
        for (int i = 0; i < c; i++)
            tower[i] = find_idx(city[i]);

        vec<vec<int>> edges(c, vec<int>(c, INF));
        for (int i = 0; i < r; i++) {
            int s, e, count = 0;
            cin >> s >> e;
            s--, e--;

            // cout << "<-------- " << s << ' ' << e << endl;
            // cout << city[s] << ", " << city[e] << endl;
            
            double now = 0;
            int idx = tower[s];
            while (idx != tower[e]) {
                count++;
                double L = now, R = dis(city[s], city[e]);
                while (fcmp(L, R, 1e-6)) {
                    // cout << L << ' ' << R << endl;
                    double M = (L+R) / 2;
                    
                    int t = find_idx(city[s], city[e], M);
                    
                    if (t == idx) {
                        L = M;
                    } else {
                        R = M;
                    }
                }

                // cout << ret << endl;
                
                for (int i = 0; i < BTS.size(); i++) {
                    if (i == idx) continue;
                    
                    if (fcmp(dis(ret, BTS[idx]), dis(ret, BTS[i]), 1e-4) == 0) {
                        idx = i;
                        break;
                    }
                }
            }  

            edges[s][e] = edges[e][s] = count;    
        }

        for (int i = 0; i < q; i++) {
            int s, e;
            cin >> s >> e;
            s--, e--;

            auto tmp = edges;

            for (int si = 0; si < c; si++) {
                for (int sk = 0; sk < c; sk++) {
                    for (int sj = 0; sj < c; sj++)
                        if (tmp[si][sk] + tmp[sk][sj] < tmp[si][sj])
                            tmp[si][sj] = tmp[si][sk] + tmp[sk][sj];
                }
            }

            cout << (tmp[s][e] == INF ? "Impossible" : to_string(tmp[s][e])) << '\n';
        }
    }
}