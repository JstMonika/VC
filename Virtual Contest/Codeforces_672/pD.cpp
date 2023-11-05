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
ofstream operator<<(ofstream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int n, k;
    cin >> n >> k;
    
    vec<pii> _list(n);
    vec<int> tmp;
    for (auto &i : _list)
    {
        cin >> i.F >> i.S;
        tmp.eb(i.F);
        tmp.eb(i.S);
    }
    
    sort(al(_list));
    
    sort(al(tmp));
    tmp.resize(distance(tmp.begin(), unique(al(tmp))));
    
    for (auto &i : _list)
    {
        i.F = distance(tmp.begin(), lower_bound(al(tmp), i.F));
        i.S = distance(tmp.begin(), lower_bound(al(tmp), i.S));
    }
    
    int sz = tmp.size();
    vec<ll> count(sz);
    
    ll now = 0, ans = 0, last = 0;
    REP(i, n)
    {
        now++;
        
        if (now == k)
            ans += 1;
        else if (now > k)
            ans += now-1;
        
        ans %= 998244353;
        
        count[_list[i].S]++;
        
        for (int k = last; k <= _list[i].F; k++)
            if (count[k])
            {
                now -= count[k];
                count[k] = 0;
            }
        
        last = _list[i].F;
        
        cout << _list[i].F << ' ' << _list[i].S << endl;
        debug(ans);
        debug(last);
        devec(count);
        cout << endl;
    }
    
    cout << ans << endl;
}