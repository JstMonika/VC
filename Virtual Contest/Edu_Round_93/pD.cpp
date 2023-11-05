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
#define debugv(v, n) cout << " > " << #v << ": "; REP(i, n) cout << v[i] << ' '; cout << endl;

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

int dp[220][220][220];
int main()
{
    int num[3];
    
    REP(i, 3)
        cin >> num[i];
    
    vec< vec<int> > _list(3);
    
    REP(i, 3)
    {
        REP(k, num[i])
        {
            int tmp;
            cin >> tmp;
            
            _list[i].eb(tmp);
        }
        
        sort(al(_list[i]), greater<int>());
    }
    
    int ans = 0;
    REP(i, num[0]+1)
        REP(j, num[1]+1)
            REP(k, num[2]+1)
            {
                if (i and j)
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j-1][k] + _list[0][i-1] * _list[1][j-1]);
                    
                if (i and k)
                    dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + _list[0][i-1] * _list[2][k-1]);
                    
                if (j and k)
                    dp[i][j][k] = max(dp[i][j][k], dp[i][j-1][k-1] + _list[1][j-1] * _list[2][k-1]);
                
                ans = max(ans, dp[i][j][k]);
            }
    
    cout << ans << endl;
}