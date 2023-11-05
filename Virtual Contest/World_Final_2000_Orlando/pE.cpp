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

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
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

int n;
int bw[110][110] = {0};
bool vis[110];
int parent[110];
ll sum = 0;

void add_path(int s, int t) {
    int _min = INF;
    
    int now = t;
    while (now != s) {
        _min = min(_min, bw[parent[now]][now]);
        
        now = parent[now];
    }
    
    
    now = t;
    while (now != s) {
        bw[parent[now]][now] -= _min;
        bw[now][parent[now]] += _min;
        
        now = parent[now];
    }
    
    // debug(_min);
    sum += _min;
}

bool bfs(int s, int t) {
    
    memset(vis, 0, sizeof(vis));
    memset(parent, 0, sizeof(parent));
    
    queue<int> q;
    q.push(s);
    vis[s] = true;
    
    while (!q.empty()) {
        int now = q.front();
        q.pop();
        
        for (int i = 1; i <= n; i++) {
            if (bw[now][i] > 0 and !vis[i]) {
                vis[i] = true;
                parent[i] = now;
                
                q.push(i);
            }
        }
    }
    
    // for (int i = 1; i <= 4; i++) {  cout << parent[i] << ' ';}
    // cout << endl;
    return vis[t];
}

int main()
{
    yccc;
    
    int cont = 1;
    while (true) {
        sum = 0;
        cin >> n;
        
        if (n == 0) break;
        
        int s, t, q;
        cin >> s >> t >> q;
        
        memset(bw, 0, sizeof(bw));
        
        for (int i = 0; i < q; i++) {
            int from, to, val;
            cin >> from >> to >> val;
            
            bw[from][to] += val;
            bw[to][from] += val;
        }
        
        while (bfs(s, t)) {
            // for (int i = 1; i <= 4; i++) {
            //     for (int j = 1; j <= 4; j++) {
            //         cout << bw[i][j] << ' ';
            //     }
            //     cout << endl;
            // }
            // cout << endl;
           
            add_path(s, t);
        }
        
        // for (int i = 1; i <= 4; i++) {
        //         for (int j = 1; j <= 4; j++) {
        //             cout << bw[i][j] << ' ';
        //         }
        //         cout << endl;
        //     }
        //     cout << endl;
        
        cout << "Network " << cont++ << endl;
        cout << "The bandwidth is " << sum << ".\n\n";
    }
}