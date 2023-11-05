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
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

void pmod(ll& a, ll b) { a = (a+b) % MOD; }
void mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; }
void tmod(ll& a, ll b) { a = (a*b) % MOD; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }

ll up[2020][2020];
ll down[2020][2020];
char ch[2020][2020];

int main()
{
    int n, m;
    cin >> n >> m;
    
    REP(i, n)
        up[i][0] = up[i][m-1] = down[i][0] = down[i][m-1] = 1;
    REP(i, m)
        up[0][i] = up[n-1][i] = down[0][i] = down[n-1][i] = 1;
        
    REP(i, n)
        REP(k, m)
            cin >> ch[i][k];
            
    REP1(i, n-2)
        REP1(k, m-2)
            if (ch[i][k] == ch[i-1][k] and ch[i][k] == ch[i][k-1] and ch[i][k] == ch[i][k+1])
                up[i][k] = min(min(up[i-1][i], up[i][k-1]), up[i][k+1]) + 1;
            else
                up[i][k] = 1;
    
    for (int i = n-2; i >= 1; i--)
        for (int k = m-2; k >= 1; k--)
            if (ch[i][k] == ch[i+1][k] and ch[i][k] == ch[i][k-1] and ch[i][k] == ch[i][k+1])
                down[i][k] = min(min(down[i+1][i], down[i][k-1]), down[i][k+1]) + 1;
            else
                down[i][k] = 1;
    
    REP(i, n)
    {
        REP(k, m)
            cout << up[i][k] << ' ';
        cout << endl;
    }
    ll sum = 0;
    REP(i, n)
        REP(k, m)
            sum += min(up[i][k], down[i][k]);
            
    cout << sum << endl;
}