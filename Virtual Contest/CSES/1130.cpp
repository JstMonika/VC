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

vec<int> parent;
vec<vec<int>> edge;
vec<int> match;

void dfs(int now, int prev) {
    for (int i = 0; i < edge[now].size(); i++) {
        if (edge[now][i] != prev) {
            parent[edge[now][i]] = now;
            dfs(edge[now][i], now);
        }
    }
}

int matching(int root) {
    
    for (int i = 0; i < edge[root].size(); i++) {
        match[edge[root][i]] = matching(edge[root][i]);
    }
    
    vec<int> count(edge[root].size());
    int sum = 0;
    for (int i = 0; i < edge[root].size(); i++) {
        for (int k = 0; k < edge[edge[root][i]].size(); k++) {
            int idx = edge[edge[root][i]][k];
            count[i] += match[idx];
        }
        
        sum += match[edge[root][i]];
    }
    
    int _max = -1;
    for (int i = 0; i < count.size(); i++) {
        _max = max(_max, count[i] + sum - match[edge[root][i]] + 1);
    }
    
    _max = max(_max, sum);
    
    match[root] = _max;
    return _max;
}

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    edge.resize(n);
    for (int i = 0; i < n-1; i++) {
        int e, f;
        cin >> e >> f;
        
        edge[e-1].eb(f-1);
        edge[f-1].eb(e-1);
    }
    
    parent.resize(n);
    parent[0] = -1;
    dfs(0, -1);
    
    edge.clear();
    edge.resize(n);
    for (int i = 0; i < n; i++) {
        if (parent[i] != -1)
            edge[parent[i]].eb(i);
    }
    
    match.resize(n, -1);
    cout << matching(0) << endl;
    
    // devec(parent);
    // devec(match);
}