#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1000000000;
const int nINF = numeric_limits<int>::min();
const ll llINF = numeric_limits<long long>::max();
const int MOD = 1e9+7;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll mPOW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll nPOW(ll a, ll b) { ll res=1; do { if(b%2) res*=a; a*=a; } while (b>>=1); return res; }
ll mFAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
ll nFAC(ll a) { ll res = 1; REP1(i, a) res*=i; return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Edge {
    int e, f, v;
    
    Edge(int e, int f, int v) : e(e), f(f), v(v) {}
};

int n, m;

vec<ll> val, parent, ans;
vec<Edge> edge;
deque<bool> vis;

bool bellmanford(int src) {
    val[src] = 0;
    vis[src] = true;
    
    bool update = true;
    for (int i = 0; i < n-1; i++) {
        if (!update)
            break;
        update = false;
        
        for (int k = 0; k < m; k++) {
            int e = edge[k].e, f = edge[k].f, v = edge[k].v;
            
            if (val[e] + v < val[f]) {
                update = true;
                
                vis[f] = true;
                parent[f] = e;
                val[f] = val[e] + v;
                // cout << "update " << f << "'s parent from " << parent[f] << " to " << e << endl;
            }
        }
    }
    
    // devec(parent);
    
    for (int i = 0; i < m; i++) {
        int e = edge[i].e, f = edge[i].f, v = edge[i].v;
            
        if (val[e] + v < val[f]) {
            parent[f] = e;
            
            int vertex = f;
            for (int k = 0; k < n; k++)
                vertex = parent[vertex];
                
            ans.eb(vertex);
            while (ans.size() == 1 or ans.back() != ans.front()) {
                ans.eb(parent[vertex]);
                vertex = parent[vertex];
            }
            
            reverse(al(ans));
            
            return false;
        }
    }
    
    return true;
}

int main()
{
    yccc;
    
    cin >> n >> m;
    
    val.resize(n+1, INF);
    parent.resize(n+1);
    vis.resize(n+1);
    
    int e, f, v;
    for (int i = 0; i < m; i++) {
        cin >> e >> f >> v;
        edge.eb(e, f, v);
    }
    
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            if (!bellmanford(i)) {
                cout << "YES\n";
                for (int k = 0; k < ans.size(); k++) {
                    cout << ans[k] << " \n"[k == ans.size()-1];
                }
                
                return 0;
            }
        }
    }
    
    cout << "NO\n";
}