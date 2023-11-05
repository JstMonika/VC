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

bool _map[10][10][4][4] = {0}; 
vec<pii> ans;
int sr, sc, er, ec;
char DIR[4] = {'N', 'E', 'S', 'W'};
char PLUS[3] = {'L', 'F', 'R'};

bool vis[10][10][4];
tuple<int, int, int> parent[10][10][4];

tuple<int, int, int> trans(int r, int c, int go) {
    switch (go) {
        case 0:
            return make_tuple(r-1, c, (go+2)%4);
        case 1:
            return make_tuple(r, c+1, (go+2)%4);
        case 2:
            return make_tuple(r+1, c, (go+2)%4);
        case 3:
            return make_tuple(r, c-1, (go+2)%4);
    }
}

bool dfs(tuple<int, int, int> src) {
    memset(vis, 0, sizeof(vis));
    memset(parent, 0, sizeof(parent));
    
    /*
    int r, c, from;
    tie(r, c, from) = src;
    
    if (r == er and c == ec) {
        ans.eb(r, c);
        return true;
    }
    
    if (vis[r][c][from])
        return false;
        
    vis[r][c][from] = true;
    
    for (int i = 0; i < 4; i++) {
        if (_map[r][c][from][i]) {
            if (dfs(trans(r, c, i))) {
                ans.eb(r, c);
                return true;
            }
        }
    }
    */
    
    queue<tuple<int, int, int>> q;
    q.emplace(src);
    
    int tr, tc, tf;
    tie(tr, tc, tf) = src;
    parent[tr][tc][tf] = make_tuple(sr, sc, -1);
    
    while (!q.empty()) {
        auto now = q.front();
        q.pop();
        
        int r, c, from;
        tie(r, c, from) = now;
        
        if (r == er and c == ec) {
            while (from != -1) {
                ans.eb(r, c);
                
                tie(r, c, from) = parent[r][c][from];
            }
            
            return true; 
        }
        
        /*
        if (vis[r][c][from])
            continue;
        vis[r][c][from] = true;
        */
       
        for (int i = 0; i < 4; i++) {
            if (_map[r][c][from][i]) {
                int tr, tc, tf;
                tie(tr, tc, tf) = trans(r, c, i);
                
                if (!vis[tr][tc][tf]) {
                    
                    vis[tr][tc][tf] = true;
                    q.emplace(trans(r, c, i));
                        
                    parent[tr][tc][tf] = now;
                }
                
                // cout << "set parent[" << tr << "][" << tc << "][" << tf << "] as [" << r << "][" << c << "][" << from << "]" << endl << flush;
            }
        }
    }
    
    return false;
}

int main()
{
    yccc;
    
    map<char, int> mDIR;
    for (int i = 0; i < 4; i++)
        mDIR[DIR[i]] = i;
    
    map<char, int> mPLUS;
    for (int i = 0; i < 3; i++)
        mPLUS[PLUS[i]] = i+1;
    
    string str;
    while (cin >> str) {
        if (str == "END")
            break;
        
        memset(_map, 0, sizeof(_map));
        
        char dir;
        cin >> sr >> sc >> dir >> er >> ec;
        tuple<int, int, char> start = make_tuple(sr, sc, dir);
        
        int r, c;
        while (cin >> r) {
            if (r == 0)
                break;
            
            cin >> c;
            
            string next;
            while (cin >> next) {
                if (next == "*")
                    break;
                
                int from = (mDIR[next[0]] + 2) % 4;
                for (int i = 1; i < next.size(); i++) {
                    _map[r][c][from][(from + mPLUS[next[i]]) % 4] = true;
                }
            }
        }
        
        ans.clear();
        memset(vis, 0, sizeof(vis));
        
        if (dfs(trans(sr, sc, mDIR[dir]))) {
            // solution.
            cout << str << endl;
            
            ans.eb(sr, sc);
            reverse(al(ans));
            for (int i = 0; i < ans.size(); i++) {
                if (i % 10 == 0) {
                    if (i != 0) cout << endl;
                    cout << "  ";
                } else {
                    cout << " ";
                }
                
                cout << '(' << ans[i].F << ',' << ans[i].S << ')';
            }
            
            cout << endl;
        } else {
            // no solution.
            cout << str << endl;
            cout << "  No Solution Possible\n";
        }
    }
}