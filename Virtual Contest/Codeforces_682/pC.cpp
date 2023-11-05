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
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int _list[110][110];
int m, n;

bool check(int src)
{
    int i = src / n;
    int k = src % n;
    
    if (i != 0 and _list[i][k] == _list[i-1][k])
        return false;
    if (k != 0 and _list[i][k] == _list[i][k-1])
        return false;
    if (i != m-1 and _list[i][k] == _list[i+1][k])
        return false;
    if (k != n-1 and _list[i][k] == _list[i][k+1])
        return false;
    
    return true;
}

bool DFS(int src)
{
    if (src == m * n)
        return true;
        
    cout << src << endl;
    
    if (check(src))
        if (DFS(src+1))
            return true;
    
    cout << src << " plus\n";
    _list[src / n][src % n]++;
    
    if (check(src))
        if (DFS(src+1))
            return true;
    
    cout << src << " minus\n";
    _list[src / n][src % n]--;
    
    return false;
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--)
    {
        cin >> m >> n;
        
        REP(i, m)
            REP(k, n)
                cin >> _list[i][k];
        
        DFS(0);
        
        REP(i, m)
            REP(k, n)
                cout << _list[i][k] << " \n"[k == n-1];
    }
}