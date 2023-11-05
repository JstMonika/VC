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
#define gt(x, v) get<v>(x)

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

int v, e;

vec<int> find_set(const vec<vec<p<int>>>& G, deq<bool>& type) {
    vec<int> inDeg(v);
    deq<bool> vis(v);
    vec<set<int>> parent(v);
    
    for (int i = 0; i < v; i++)
        for (int k = 0; k < G[i].size(); k++) {
            inDeg[G[i][k].F]++;
            parent[G[i][k].F].emplace(i);
        }
        
    vec<int> que;
    queue<int> zero;
    for (int i = 0; i < v; i++) if (inDeg[i] == 0) zero.emplace(i);
    
    while (!zero.empty()) {
        auto now = zero.front();
        zero.pop();
        
        for (auto i : G[now]) {
            if (--inDeg[i.F] == 0) {
                zero.emplace(i.F);
            }
        }
        
        que.eb(now);
    }
    
    vec<int> val(v, INF);
    
    val[que[0]] = 0;
    type[que[0]] = true;
    
    for (int i = 1; i < v; i++) {
        bool good = true;
        
        for (auto k : parent[que[i]]) {
            int eVal, p;
            for (auto r : G[k]) {
                if (r.F == que[i]) {
                    eVal = r.S;
                    p = k;
            
                    if (val[que[i]] == INF) {
                        val[que[i]] = val[p] + eVal;
                        
                        if (!type[p]) {
                            good = false;
                            break;
                        }
                    } else {
                        if (!type[p] or val[que[i]] != val[p] + eVal) {
                            good = false;
                            break;
                        }
                    }
                }
            }
            
            if (!good) break;
        }
        
        if (good)
            type[que[i]] = true;
    }
    
    return val;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> v >> e) {
        if (!v) break;
        vec<tuple<int, int, int>> edges;
        
        vec<vec<p<int>>> G(v), rG(v);
        for (int i = 0; i < e; i++) {
            int a, b, val;
            cin >> a >> b >> val;
            edges.eb(a-1, b-1, val);
            
            G[a-1].eb(b-1, val);
            rG[b-1].eb(a-1, val);
        }
        
        deq<bool> A(v), B(v);
        
        vec<int> vA = find_set(G, A);
        vec<int> vB = find_set(rG, B);
        
        // devec(A);
        // devec(B);
        // devec(vA);
        // devec(vB);
        // debug(v);
        
        bool good = true;
        for (int i = 0; i < v; i++) {
            if (!A[i] and !B[i])
                good = false;
        }
        
        // debug(good);
        
        if (good) {   
            int _max = -1;
            vec<int> bridge;
            for (int i = 0; i < e; i++) {
                if (A[gt(edges[i], 0)] and !A[gt(edges[i], 1)]) {
                    bridge.eb(i);
                    _max = max(_max, vA[gt(edges[i], 0)] + vB[gt(edges[i], 1)] + gt(edges[i], 2));
                }
            }
            
            if (_max != -1) {
                vec<p<int>> ans;
                for (auto i : bridge) {
                    if (vA[gt(edges[i], 0)] + vB[gt(edges[i], 1)] + gt(edges[i], 2) != _max)
                        ans.eb(i+1, _max - (vA[gt(edges[i], 0)] + vB[gt(edges[i], 1)] + gt(edges[i], 2)));
                }
                
                cout << "Case " << c++ << ": " << ans.size() << ' ' << _max << endl;
                for (auto i : ans)
                    cout << i.F << ' ' << i.S << endl;
            } else {
                cout << "Case " << c++ << ": " << 0 << ' ' << vA[v-1] << endl;
            }
        } else {
            cout << "Case " << c++ << ": No solution\n";
        }
    }
}