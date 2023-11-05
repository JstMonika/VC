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

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const ll llINF = numeric_limits<long long>::max();
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

int main()
{
    yccc;
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        if (!n)
            break;
        
        vec<pii> _list(m);
        vec<int> level(n);
        for (auto &i : _list) {
            cin >> i.F >> i.S;
            
            i.F--;
            i.S--;
            
            // cout << i.F << ' ' << i.S << endl;
            level[i.F] = level[i.S] = 1 + max(level[i.F], level[i.S]);
            // cout << i.F << ' ' << i.S << endl;
        }
        
        int t = *max_element(al(level));
        
        bool good = true;
        
        for (ll i = 0; i < (1ll << n); i++) {
            deque<bool> s(n);
            for (int k = 0; k < n; k++)
                s[k] = (i >> k);
                
            for (int k = 0; k < m; k++) {
                if (s[_list[k].F] > s[_list[k].S])
                    swap(s[_list[k].F], s[_list[k].S]);
            }
            
            for (int k = 0; k < n-1; k++) {
                if (s[k] > s[k+1]) {
                    good = false;
                    
                    cout << "Case " << c++ << " is not a sorting network and operates in " << t << " time units.\n";
                    
                    break;
                }
            }
            
            if (!good)
                break;
        }
        
        if (good) {
            cout << "Case " << c++ << " is a sorting network and operates in " << t << " time units.\n";
        }
    }
}