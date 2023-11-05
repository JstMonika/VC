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

int seg[1000];
int a[1000];

int pull(int x, int y) { return seg[x] + seg[y] }
void build(int idx, int l, int r) 
{
    if (l == r)
    {
        seg[idx] = a[l];
        return;
    }
    
    int m = (l+r) / 2;
    build(idx*2, l, m);
    build(idx*2+1, m+1, r);
    seg[idx] = pull(idx*2, idx*2+1);
}
int query(int idx, int l, int r, int ql, int qr)
{
    if (l >= ql and r <= qr)
        return seg[idx];
    
    if (r < ql or l > qr)
        return 0;
    
    int m = (l+r) / 2;
    return pull(
        query(idx*2, l, m, ql, qr),
        query(idx*2+1, m+1, r, ql, qr));
}

void update(int idx, int l, int r, int q, int v)
{
    if (l == r)
    {
        seg[l] = v;
        return;
    }
    
    int m = (l+r) / 2;
    if (q <= m)
        update(idx*2, l, m, q, v);
    else
        update(idx*2+1, m, r, q, v);
    
    seg[idx] = pull(idx*2, idx*2+1);
}


int main()
{
    yccc;
}