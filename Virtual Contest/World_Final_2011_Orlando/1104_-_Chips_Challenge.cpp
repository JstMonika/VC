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

struct Edge {
    int v, f, cost;
    
    Edge() {}
    Edge(int v, int f, int cost) : v(v), f(f), cost(cost) {}
};

#define Source 0
#define ROW(i) (i*3+1)
#define COLUMN(i) (i*3+2)
#define K(i) (i*3+3)
#define Terminate (3*n+1)

int n;

vec<vec<int>> V;
vec<Edge> E;

inline int find(int st, int ed) {
    cout << st << ' ' << ed << endl;
    for (auto i : V[st]) {
        cout << i << endl;
        if (E[i].v == ed) return i;
    }
}

vec<int> Epa;
bool find_path() {
    vec<int> dp(3*n+2, 10), parent(3*n+2), parentE(3*n+2);
    dp[Source] = 0;
    parent[Source] = -1;
    
    queue<int> que;
    que.emplace(0);
    
    while (!que.empty()) {
        auto now = que.front();
        que.pop();
        
        for (auto i : V[now]) {
            if (E[i].f > 0 and dp[now] + E[i].cost < dp[E[i].v]) {
                // cout << now << ' ' << E[i].v << ": from " << dp[E[i].v] << " to " << dp[now] + E[i].cost << endl;
                    
                parentE[E[i].v] = i;
                parent[E[i].v] = now;
                dp[E[i].v] = dp[now] + E[i].cost;
                
                que.emplace(E[i].v);
            }
        }
    }
    
    vec<int> _list;
    if (dp[Terminate] != 10) {
        Epa.clear();
        
        int it = Terminate;
        while (parent[it] != -1) {
            _list.eb(it);
            Epa.eb(parentE[it]);
            it = parent[it];
        }
        
        // devec(dp);
        // devec(_list);
        // devec(parent);
        return true;
    }
    
    // devec(dp);
    return false;
}

p<int> MCMF() {
    int maxFlow = 0, minCost = 0;
    
    while (find_path()) {
        
        int curFlow = INF;
        for (auto i : Epa)
            curFlow = min(curFlow, E[i].f);
        
        for (auto i : Epa) {
            E[i].f -= curFlow;
            E[i^1].f += curFlow;
            
            minCost += E[i].cost * curFlow;
        }
        
        maxFlow += curFlow;
        
        // cout << "find: " << curFlow << ' ' << minCost << endl;
    }
    
    return {maxFlow, minCost};
}

int main()
{
    yccc;
    
    int A, B, cases = 1;
    while (cin >> n >> A >> B) {
        if (!n) break;
        
        V.clear();
        E.clear();
        
        V.resize(3*n+2);
        
        int nC = 0, nE = 0;
        vec<int> r(n), c(n);
        for (int i = 0; i < n; i++) {
            string str;
            cin >> str;
            
            for (int k = 0; k < n; k++) {
                if (str[k] != '/') {
                    r[i]++, c[k]++, nE++;
                    
                    if (str[k] == 'C') 
                        nC++;
                    else {
                        // cout << ROW(i) << " to " << COLUMN(k) << endl;
                        V[ROW(i)].eb(E.size());
                        E.eb(COLUMN(k), 1, 1);
                        V[COLUMN(k)].eb(E.size());
                        E.eb(ROW(i), 0, -1);
                    }
                } 
            }
        }
        
        for (int i = 0; i < n; i++) {
            V[COLUMN(i)].eb(E.size());
            E.eb(K(i), INF, 0);
            V[K(i)].eb(E.size());
            E.eb(COLUMN(i), 0, 0);
            
            V[K(i)].eb(E.size());
            E.eb(Terminate, c[i], 0);
            V[Terminate].eb(E.size());
            E.eb(K(i), 0, 0);
            
            V[Source].eb(E.size());
            E.eb(ROW(i), r[i], 0);
            V[ROW(i)].eb(E.size());
            E.eb(Source, 0, 0);
        }
        
        // devec2(V);
        
        int ans = -1;
        bool first = true;
        auto tmpE = E;
        for (int limit = 0; limit <= n; limit++) {
            // cout << "limit: " << limit << endl;
            E = tmpE;
            for (int k = 0; k < n; k++) {
                if (first) V[ROW(k)].eb(E.size());
                E.eb(K(k), limit, 0);
                if (first) V[K(k)].eb(E.size());
                E.eb(ROW(k), 0, 0);
            }
            
            int maxFlow, minCost;
            tie(maxFlow, minCost) = MCMF();
            
            // cout << maxFlow << ' ' << nE << ' ' << maxFlow - minCost - nC << endl;
            if (maxFlow == nE and limit * B <= (maxFlow - minCost) * A) {
                ans = max(maxFlow - minCost - nC, ans);
            }
            
            first = false;
        }
        
        cout << "Case " << cases++ << ": ";
        
        if (ans == -1) cout << "impossible" << endl;
        else cout << ans << endl;
    }
}