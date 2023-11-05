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

vec<int> _list;
ll ans;

void merge(int l, int r) {
    if (l == r)
        return;
    
    int m = (l+r) / 2;
    merge(l, m);
    merge(m+1, r);
    
    vec<int> tmp(r-l+1);
    
    int i = l, k = m+1, idx = 0;
    while (i != m+1 and k != r+1) {
        if (_list[i] > _list[k]) {
            tmp[idx++] = _list[k++];
            
            ans += (m+1-i);
        } else {
            tmp[idx++] = _list[i++];
        }
    }
    
    while (i != m+1) tmp[idx++] = _list[i++];
    while (k != r+1) tmp[idx++] = _list[k++];
    
    for (i = l; i <= r; i++) {
        _list[i] = tmp[i-l];
    }
    
    return;
}

int main()
{
    yccc;
    
    int n;
    while (cin >> n) {
        if (n == 0)
            break;
        
        ans = 0;
        _list.resize(n);
        for (auto &i : _list)
            cin >> i;
            
        merge(0, n-1);
        
        cout << ans << endl;
    }
}