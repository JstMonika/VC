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

char _map[1010][1010];
int P[1010][1010];
int M[1010][1010];
int path[1010][1010];
int n, m;

int gx[4] = {0, 0, -1, 1};
int gy[4] = {1, -1, 0, 0};
char ch[4] = {'R', 'L', 'U', 'D'};

bool check(int i, int k, int mode) {
    if (i < 0 or i >= n) return false;
    if (k < 0 or k >= m) return false;
    
    if (!mode) {
        if (_map[i][k] == '#')
            return false;
            
        if (P[i][k] != -1)
            return false;
    } else if (mode == 1) {
        if (_map[i][k] == '#')
            return false;
            
        if (M[i][k] != -1)
            return false;
    } else {
        if (_map[i][k] == '#' or (M[i][k] != -1 and M[i][k] <= P[i][k]))
            return false;
    }
    
    return true;
}

vec<pair<int, deque<char>>> tans;
set<pii> sPath;
bool dfs(pii now, pii prev, int depth, deque<char>& ans) {
    // cout << now.F << ' ' << now.S << endl;
    // cout << flush;
    
    if (now.F == 0 or now.F == n-1 or now.S == 0 or now.S == m-1) {
        //* print ans.
        
        tans.emplace_back(depth, ans);
        
        return true;
    }
    
    for (int i = 0; i < 4; i++) {
        if (check(now.F + gx[i], now.S + gy[i], 2)) {
            if (make_pair(now.F + gx[i], now.S + gy[i]) != prev and sPath.find(make_pair(now.F + gx[i], now.S + gy[i])) == sPath.end()) {
                ans.push_back(ch[i]);
                sPath.insert(make_pair(now.F + gx[i], now.S + gy[i]));
                
                dfs(make_pair(now.F + gx[i], now.S + gy[i]), now, depth+1, ans);
                
                sPath.erase(make_pair(now.F + gx[i], now.S + gy[i]));
                ans.pop_back();
            }
        }
    }
    
    return false;
}

void clear(queue<pii>& src) {
    queue<pii> tmp;
    swap(tmp, src);
}

int main()
{   
    memset(P, -1, sizeof(P));
    memset(M, -1, sizeof(M));
    
    yccc;
        
    cin >> n >> m;
    
    vec<pii> out, Mons;
    pii player;
    
    for (int i = 0; i < n; i++) {
        cin.get();
        for (int k = 0; k < m; k++) {
            cin >> _map[i][k];
            
            if (_map[i][k] == 'M') {
                Mons.eb(i, k);
            } else if (_map[i][k] == 'A') {
                player = make_pair(i, k);
            }
        }
    }
    
    int val = 0;
    queue<pii> que, tmp;
    
    tmp.push(player);
    P[player.F][player.S] = 0;
    
    while (tmp.size() > 0) {
        que = tmp;
        clear(tmp);
        
        val++;
        
        while (que.size() > 0) {   
            auto now = que.front();
            que.pop();
            
            for (int i = 0; i < 4; i++) {
                if (check(now.F + gx[i], now.S + gy[i], 0)) {
                    P[now.F + gx[i]][now.S + gy[i]] = val;
                    tmp.emplace(now.F + gx[i], now.S + gy[i]);
                }
            }
        }
    }
    
    // for (int i = 0; i < n; i++) {
    //     for (int k = 0; k < m; k++)
    //         cout << P[i][k] << '\t';
    //     cout << endl;
    // }
    
    // cout << flush;
    
    val = 0;
    for (int i = 0; i < Mons.size(); i++) {    
        tmp.emplace(Mons[i].F, Mons[i].S);
        M[Mons[i].F][Mons[i].S] = 0;
    }
    
    while (tmp.size() > 0) {
        que = tmp;
        clear(tmp);
        
        val++;
        
        while (que.size() > 0) {   
            auto now = que.front();
            que.pop();
            
            for (int i = 0; i < 4; i++) {
                if (check(now.F + gx[i], now.S + gy[i], 1)) {
                    M[now.F + gx[i]][now.S + gy[i]] = val;
                    tmp.emplace(now.F + gx[i], now.S + gy[i]);
                }
            } 
        }
    }
    
    // for (int i = 0; i < n; i++) {
    //     for (int k = 0; k < m; k++)
    //         cout << M[i][k] << '\t';
    //     cout << endl;
    // }
    
    // cout << flush;
    
    deque<char> ans;
    dfs(player, make_pair(-1, -1), 0, ans);
    
    if (tans.size()) {
        sort(al(tans));
        
        cout << "YES\n" << tans[0].F << endl;
        for (int i = 0; i < tans[0].S.size(); i++) {
            cout << tans[0].S[i];
        }
        
        cout << endl;
    } else 
        cout << "NO\n";
}