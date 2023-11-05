#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
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
bool _list[15][15];
bitset<15> vis, basic;

bool valid(int i) {
    int count = 0;
    for (int k = 0; k < 15; k++) {
        if (!vis[k] and _list[i][k])
            count++;
    }
    
    return ((count == 1 || count == 0) && !vis[i]);
}

bool dfs(int prev, int now) {
    vis.set(now);
    
    int count = 0, go = -1;
    
    for (int i = 0; i < 15; i++) {
        if (_list[now][i] and vis[i] and !basic[i] and prev != i) {
            // cout << "at [" << now+1 << "][" << i+1 << "] return false\n";
            return false;
        }
        
        if (_list[now][i] and !vis[i]) {
            go = i;
            count++;
        }
    }
    
    if (go == -1)
        return true;
    
    if (count == 1) {
        return dfs(now, go);
    }
    
    // cout << "at " << now+1 << " too much option\n";
    return false;
}

bool check(int _set) {
    // cout << _set << ":\n";
    vis = basic = bitset<15>(_set); 
    
    int count = 0, _max = vis.count() + 1;
    
    for (int i = 0; i < n; i++) {
        if (valid(i)) {
            // for (int i = 0; i < n; i++) {
            //     cout << vis[i];
            // }
            // cout << endl;
            
            if (!dfs(-1, i))
                return false;
            
            count++;
        }
    }
    
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            // cout << "Not visit " << i+1 << endl;
            return false;
        }
    }
    
    // cout << _set << ": " << count << endl;
    
    return (count <= _max);
}

int main()
{   
    yccc;
    
    int c = 1;
    while (true) {
        memset(_list, 0, sizeof(_list));
        
        cin >> n;
        
        if (n == 0) break;
        
        int a, b;
        while (cin >> a >> b) {
            if (a == -1)
                break;
            
            a--;
            b--;
                
            _list[a][b] = true;
            _list[b][a] = true;
        }
        
        ll ans = INF;
        for (int i = 0; i < (1 << n); i++) {
            if (check(i)) {
                // cout << i << endl;
                bitset<16> num(i);
                ans = min(ans, ll(num.count()));
            }
        }
        
        cout << "Set " << c++ << ": Minimum links to open is " << ans << endl;
    }
}