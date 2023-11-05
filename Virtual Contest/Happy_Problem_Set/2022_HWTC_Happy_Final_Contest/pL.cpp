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

int main()
{
    yccc;
    
    int n, m, h, w;
    cin >> n >> m >> h >> w;
    
    vec<vec<int>> _list(n, vec<int>(m));
    for (auto &i : _list)
        for (auto &k : i)
            cin >> k;
    
    ll L = 1, R = n*m, ans = INF;
    while (L <= R) {
        ll M = (L+R) / 2;
        
        vec<vec<int>> pre(n+1, vec<int>(m+1));
        for (int i = 1; i <= n; i++)
            for (int k = 1; k <= m; k++) {
                pre[i][k] = pre[i][k-1] + pre[i-1][k] - pre[i-1][k-1];
                
                if (_list[i-1][k-1] < M) {
                    pre[i][k]--;
                } else if (_list[i-1][k-1] > M) {
                    pre[i][k]++;
                }
            }
        
        for (int i = h; i <= n; i++) {
            for (int k = w; k <= m; k++) {
                if (pre[i][k] - pre[i-h][k] - pre[i][k-w] + pre[i-h][k-w] == 0) ans = min(ans, M);
                
                if (pre[i][k] - pre[i-h][k] - pre[i][k-w] + pre[i-h][k-w] < 0) R = M-1;
            }
        }
        
        if (R != M-1)
            L = M+1;
    }
    
    cout << ans << endl;
}