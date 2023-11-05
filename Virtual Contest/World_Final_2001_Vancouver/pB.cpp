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

class Point {
    public:
    
    int x, y, z, r;
    
    Point() {}
    Point(int x, int y, int z, int r) : x(x), y(y), z(z), r(r) {}
};

vec<Point> _list;
vec<vec<double>> adj;

double distance(int i, int k) {
    int x = _list[i].x - _list[k].x;
    int y = _list[i].y - _list[k].y;
    int z = _list[i].z - _list[k].z;
    
    return sqrt(x*x + y*y + z*z);
}

deque<bool> vis;
vec<double> dis;

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (n == -1)
            break;
            
        _list.resize(n+2);
        for (int i = 0; i < n; i++)
            cin >> _list[i].x >> _list[i].y >> _list[i].z >> _list[i].r;
        
        for (int i = n; i < n+2; i++) {
            cin >> _list[i].x >> _list[i].y >> _list[i].z;
            _list[i].r = 0;
        }
        
        adj.resize(n+2);
        
        for (int i = 0; i < n+2; i++) {
            adj[i].resize(n+2);
            
            for (int k = 0; k < n+2; k++) {
                adj[i][k] = max(0.0, distance(i, k) - _list[i].r - _list[k].r);
            }
        }
        
        vis.clear();
        vis.resize(n+2);
        dis.clear();
        dis.resize(n+2, numeric_limits<double>::max());
        
        using pdi = pair<double, int>;
        priority_queue<pdi, vec<pdi>, greater<pdi>> pq;
        
        //* n: start, n+1: end.
        pq.emplace(0, n);
        dis[n] = 0;
        
        auto now = pq.top();
        for (int i = 0; i < n+2; i++) {
            do {
                now = pq.top();
                pq.pop();
            } while (vis[now.S]);
            
            vis[now.S] = true;
            
            for (int k = 0; k < n+2; k++) {
                if (!vis[k] and dis[k] > dis[now.S] + adj[now.S][k]) {
                    dis[k] = dis[now.S] + adj[now.S][k];
                    pq.emplace(dis[k], k);
                }
            }
        }
        
        cout << "Cheese " << c++ << ": Travel time = " << fixed << setprecision(0) << dis[n+1]*10 << " sec\n";
    }
}