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

int n, Ycount;
vec<vec<int>> G;
vec<int> _list, parent;
deq<bool> AP, vis;

void dfs(int now, int prev) {
    // debug(now);
    _list[now] = parent[now] = Ycount++;
    
    bool first = true;
    for (auto i : G[now]) {
        if (i == prev) continue;
        
        if (_list[i] == -1) {
            //* check if the root has two child.
            if (first) first = false;
            else if (!first and now == 1) { 
                AP[1] = true;
            }
            
            dfs(i, now);
            parent[now] = min(parent[now], parent[i]);
            
            if (parent[i] >= _list[now] and now != 1)
                AP[now] = true;
        } else //* back edge.
            parent[now] = min(parent[now], _list[i]);
    }
}

set<int> _set;
void dfs2(int now) {
    vis[now] = true;
    Ycount++;
    
    for (auto i : G[now]) {
        if (AP[i]) _set.emplace(i);
        else if (!vis[i]) dfs2(i);
    }
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n) {
        if (!n) break;
        
        ll _max = 0;
        
        G.clear();
        G.resize(n+2);
        
        _list.resize(n+2);
        fill(al(_list), -1);
        
        parent.resize(n+2);
        fill(al(parent), INF);
        
        AP.clear();
        vis.clear();
        AP.resize(n+2);
        vis.resize(n+2);
        
        for (int i = 0; i < n; i++) {
            ll a, b;
            cin >> a >> b;
            
            _max = max({_max, a, b});
            G[a].eb(b);
            G[b].eb(a);
        }
        
        Ycount = 0;
        //* finding AP
        dfs(1, -1);
        
        // devec(AP);
        // devec(_list);
        // devec(parent);
        
        //* _max: # of nodes (1 ~ _max).
        ll ans = 1, count = 0;
        for (int i = 1; i <= _max; i++) {
            //* check how many AP adjacent to this c.c.
            _set = set<int>();
            if (!vis[i] and !AP[i]) {
                //* Ycount: # of nodes in this c.c.
                Ycount = 0;
                dfs2(i);
                
                //* if # of adjacent AP is 1
                if (_set.size() == 1) {
                    ans *= Ycount;
                    count++;
                }
            }
        }
        
        if (count == 0)
            cout << "Case " << c++ << ": " << 2 << ' ' << _max * (_max-1) / 2 << endl;
        else 
            cout << "Case " << c++ << ": " << count << ' ' << ans << endl;
    }
}