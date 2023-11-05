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

vec<p<int>> edges;
deq<bool> color;

vec<vec<p<int>>> G;

deq<bool> vis;
vec<int> cycle_edge;

void dfs(int now, int prev, int c) {
    vis[now] = true;
    // debug(now);
    
    // cout << now << endl;
    for (auto i : G[now]) {
        // cout << i.F << ' ' << i.S << endl;
        if (i.F != prev) {   
            if (vis[i.F]) {
                // cout << now << ' ' << i.F << endl;
                cycle_edge.eb(i.S);
            }
            else {
                color[i.S] = c;
                dfs(i.F, now, 1-c);
            }
        }
    }
}

struct disjointSet {
    vec<int> pset;
    int _size;
        
    void initSet(int n) {
        _size = n;
        pset.resize(n);
        for (int i = 0; i < n; i++) pset[i] = i;
    }

    int findSet(int i) {
        return (pset[i] == i ? i : pset[i] = findSet(pset[i]));
    }

    void unionSet(int i, int k) {
        if (findSet(i) != findSet(k)) {
            pset[findSet(i)] = findSet(k);
            _size--;
        }
    }
};

disjointSet red, blue, bRed, bBlue;

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n, m;
        cin >> n >> m;
        
        cycle_edge.clear();
        
        edges.resize(m);
        color.resize(m);
        fill(al(color), -1);
        
        G.clear();
        G.resize(n+1);
            
        for (int i = 0; i < m; i++) {
            cin >> edges[i].F >> edges[i].S;
            
            G[edges[i].F].eb(edges[i].S, i);
            G[edges[i].S].eb(edges[i].F, i);
        }
        
        vis.resize(n+1);
        fill(al(vis), false);
        dfs(1, -1, 0);
        
        sort(al(cycle_edge));
        cycle_edge.resize(unique(al(cycle_edge)) - cycle_edge.begin());
        
        red.initSet(n);
        blue.initSet(n);
        
        for (int i = 0; i < m; i++) {
            bool good = true;
            for (auto k : cycle_edge)
                if (i == k) good = false;
            
            if (!good) continue;
            
            if (color[i]) {
                blue.unionSet(edges[i].F-1, edges[i].S-1);
            } else {
                red.unionSet(edges[i].F-1, edges[i].S-1);
            }
        }
        
        // devec(color);
        // devec(cycle_edge);
        
        bRed = red;
        bBlue = blue;
        
        ll _max = INF;
        for (int i = 0; i < (1<<cycle_edge.size()); i++) {
            red = bRed;
            blue = bBlue;
            
            for (int k = 0; k < cycle_edge.size(); k++) {
                if (i & (1 << k)) {
                    blue.unionSet(edges[cycle_edge[k]].F-1, edges[cycle_edge[k]].S-1);
                } else {
                    red.unionSet(edges[cycle_edge[k]].F-1, edges[cycle_edge[k]].S-1);
                }
            }
            
            // cout << red._size << ' ' << blue._size << endl;
            // for (int i = 0; i < m; i++)
            //     cout << color[i];
            // cout << endl;
                
            if (red._size + blue._size < _max) {
                for (int k = 0; k < cycle_edge.size(); k++)
                    color[cycle_edge[k]] = (i & (1 << k));
                
                _max = red._size + blue._size;
            }
        }
        
        for (int i = 0; i < m; i++)
            cout << color[i];
        cout << endl;
    }
}