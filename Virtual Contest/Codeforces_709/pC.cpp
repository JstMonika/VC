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

bool cmp(pair<int, vec<int>> a, pair<int, vec<int>> b)
{
    return a.S.size() < b.S.size();
}

int m;
vec<vec<int>> day;
vec<int> ans, cont;

bool dfs(int i)
{
    if (i == m)
        return true;
        
    if (ans[i] != 0)
        return dfs(i+1);
        
    for (int k = 0; k < day[i].size(); k++)
    {
        if (cont[day[i][k]] < m/2-1)
        {
            ans[i] = day[i][k];
            cont[day[i][k]]++;
            
            if (dfs(i+1))
                return true;
            
            cont[day[i][k]]--;
        }
    }
    
    return false;
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--)
    {
        int n;
        cin >> n >> m;
        
        vec<pair<int, vec<int>>> _list(n);
        day.resize(m+1);
        ans.resize(m+1);
        cont.resize(m+1);
        
        for (int i = 0; i < n; i++)
            _list[i].F = i+1;
            
        for (int i = 1; i <= m; i++)
        {
            int num;
            cin >> num;
            
            for (int k = 0; k < num; k++)
            {
                int tmp;
                cin >> tmp;
                day[i].eb(tmp);
                
                _list[tmp-1].S.eb(i);
            }
        }
        
        sort(al(_list), cmp);
        
        for (int i = 0; i < n; i++)
        {
            for (auto q : _list[i].S)
                if (ans[q] == 0)
                {
                    ans[q] = _list[i].F;
                    cont[_list[i].F]++;
                    
                    cout << cont[_list[i].F] << ' ' << (m+1)/2-1 << endl;
                    if (cont[_list[i].F] == (m+1)/2-1)
                        break;
                }
        }
        devec(ans);
        devec(cont);
        cout << (dfs(1) ? "YES\n" : "NO\n");
        for (int i = 1; i <= m; i++)
            cout << ans[i] << ' ';
    }
}