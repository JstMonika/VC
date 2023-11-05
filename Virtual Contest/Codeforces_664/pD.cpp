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

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll FAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }

int main()
{
    int n, d, m;
    cin >> n >> d >> m;
    
    vector<int> a(n);
    REP(i, n)
        cin >> a[i];
        
    sort(al(a), greater<int>());
    
    for (int i = 0; i < a.size(); i++)
        cout << a[i] << ' ';
    cout << endl;
    
    int s = 0;
    while (a[s] > m) s++;
    
    ll sum = 0;
    for (int i = 0; i < min(s, (int)a.size() / (d+1)); i++)
        sum += a[i];
    
    if (s < (a.size() / (d+1)))
    {
        for (int b = 0; s < a.size() and b <=
    }
    else
    {
        for (int k = 0; k < (a.size() % (d+1)) - 1; k++, s++)
            sum += a[s];
    }
    cout << sum << endl;
}