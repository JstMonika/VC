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

ll ret_min(vec<ll> one, vec<ll> two, int dis)
{
    vec<ll> c_one(one.size(), 0), c_two(two.size(), 0);
    c_one[0] = dis;
    c_two[0] = dis;
    
    ll ret = (one[0] + two[0]) * dis;
    ll past = ret;
    int o_idx = 0, t_idx = 0;
    
    for (int i = 2; i < dis; i++)
    {   
        if (i % 2)
        {
            if (two[i/2] < two[t_idx])
            {
                c_two[i/2] = c_two[t_idx] - 1;
            
                past -= (c_two[t_idx] - 1) * two[t_idx];
                past += c_two[i/2] * two[i/2];
                
                c_two[t_idx] = 1;
                
                t_idx = i/2;
            }
            else
            {
                c_two[i/2] = 1;
                c_two[t_idx]--;
                
                past -= two[t_idx];
                past += two[i/2];
            }
        }
        else
        {
            if (one[i/2] < one[o_idx])
            {
                c_one[i/2] = c_one[o_idx] - 1;
            
                past -= (c_one[o_idx] - 1) * one[o_idx];
                past += c_one[i/2] * one[i/2];
                
                c_one[o_idx] = 1;
                
                o_idx = i/2;
            }
            else
            {
                c_one[i/2] = 1;
                c_one[o_idx]--;
                
                past -= one[o_idx];
                past += one[i/2];
            }
        }
        
        // debug(i);
        // debug(past);
        
        ret = min(ret, past);
    }
    
    return ret;
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--)
    {
        ll n;
        cin >> n;
        
        vec<ll> a, b;
        REP(i, n)
        {
            int tmp;
            cin >> tmp;
            
            if (i % 2)
                b.eb(tmp);
            else
                a.eb(tmp);
        }
        
        ll ans = llINF;
        
        ans = min(ret_min(a, b, n), ans);
        
        cout << ans << endl;
    }
}