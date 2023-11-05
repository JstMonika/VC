#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<typename T> using vec = vector<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

set<int> _set;
vec<vec<int>> G;
vec<int> vis, parent;

int dfs(int now, int prev) {
    
    parent[now] = prev;
    if (_set.find(now) != _set.end()) {
        return now;
    }
    if (vis[now])
        return -1;
    
    vis[now] = true;
    
    _set.insert(now);
    
    for (int i = 0; i < G[now].size(); i++) {
        int tmp;
        if ((tmp = dfs(G[now][i], now)) != -1) {
            return tmp;
        }
    }
    
    _set.erase(now);
    return -1;
}

int main()
{
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    G.resize(n);
    parent.resize(n);
    vis.resize(n);
    
    for (int i = 0; i < m; i++) {
        int e, f;
        cin >> e >> f;
        
        
        G[e-1].eb(f-1);
    }
    
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int ans;
            if ((ans = dfs(i, -1)) != -1) {
                for (int i = 0; i < n; i++)
                    ans = parent[ans];
                    
                vec<int> vans;
                // vans.reserve(n+1);
                vans.eb(ans);
                
                while (vans.size() == 1 or vans.front() != vans.back()) {
                    vans.eb(parent[vans.back()]);
                }
                
                reverse(al(vans));
                
                cout << vans.size() << endl;
                for (auto i : vans)
                    cout << i+1 << ' ';
                    
                return 0;
            }
        }
    }
    
    cout << "IMPOSSIBLE";
}