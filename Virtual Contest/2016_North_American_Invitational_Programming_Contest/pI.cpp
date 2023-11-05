#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 0x3f3f3f3f;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

vec<int> dis;
vec<vec<int>> parent, G;

void dfs(int now, int prev) {
    if (now == 0) {
        dis[now] = 0;
        parent[now][0] = -1;
    }
    else {
        dis[now] = dis[prev] + 1;
        parent[now][0] = prev;
    }
        
    for (auto i : G[now]) {
        if (i != prev)
            dfs(i, now);
    }
}

ll find_dis(int u, int v) {
    int du = u, dv = v;
    
    if (dis[u] < dis[v]) swap(u, v);
    
    int sub = dis[u] - dis[v];
    for (int i = 31; i >= 0; i--) {
        if (sub & (1<<i)) u = parent[u][i];
    }
    
    if (u == v) return dis[du] + dis[dv] - 2 * dis[u];
    
    for (int i = 31; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }
    
    return dis[du] + dis[dv] - 2 * dis[parent[u][0]];
}

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    G.resize(n);
    for (int i = 0; i < n-1; i++) {
        int u, v;
        cin >> u >> v;
        
        u--, v--;
        
        G[u].eb(v);
        G[v].eb(u);
    }
    
    dis.resize(n);
    parent.resize(n);
    for (auto &i : parent)
        i.resize(32);
        
    dfs(0, -1);
    for (int i = 1; i < 32; i++) {
        for (int k = 0; k < n; k++) {
            parent[k][i] = (parent[k][i-1] == -1 ? -1 : parent[parent[k][i-1]][i-1]);
        }
    }
    
    ll ans = 0;
    for (int i = 1; i <= n; i++)
        for (int k = 2 * i; k <= n; k += i)
            ans += find_dis(i-1, k-1) + 1;
    
    cout << ans << endl;
}