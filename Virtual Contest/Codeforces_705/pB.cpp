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

int h, m;
int va, vb, vc, vd;
int dis;

bool valid(int a, int b, int c, int d)
{
    int _list[5] = {3, 4, 6, 7, 9};
    
    REP(i, 5)
    {
        if (a == _list[i]) return false;
        if (b == _list[i]) return false;
        if (c == _list[i]) return false;
        if (d == _list[i]) return false;
    }
    
    if (a == 2) a = 5;
    else if (a == 5) a = 2;
    
    if (b == 2) b = 5;
    else if (b == 5) b = 2;
    
    if (c == 2) c = 5;
    else if (c == 5) c = 2;
    
    if (d == 2) d = 5;
    else if (d == 5) d = 2;
    
    if (d * 10 + c >= h) return false;
    // cout << d*10 + c << ' ' << h << endl;
    if (b * 10 + a >= m) return false;
    
    return true;
}

void front(int a, int b, int c, int d)
{
    int cur = 0;
    while (!valid(a, b, c, d))
    {
        d++;
        
        if (d == 10)
        {
            d = 0;
            c++;
        }
        
        if (c * 10 + d == m)
        {
            c = d = 0;
            b++;
        }
        
        if (b == 10)
        {
            b = 0;
            a++;
        }
        
        if (a * 10 + b == h)
            a = b = 0;
        
        cur++;
    }
    
    if (cur < dis)
    {
        dis = cur;
        va = a;
        vb = b;
        vc = c;
        vd = d;
    }
}

void back(int a, int b, int c, int d)
{
    int cur = 0;
    while (!valid(a, b, c, d))
    {
        d--;
        
        if (d == -1)
        {
            d = 9;
            c--;
        }
        
        if (c == -1)
        {
            c = m / 10;
            d = m % 10;
            
            b--;
            
            d--;
        
            if (d == -1)
            {
                d = 9;
                c--;
            }
        }
        
        if (b == -1)
        {
            b = 9;
            a--;
        }
        
        if (a == -1)
        {
            a = h / 10;
            b = h % 10;
            
            b--;
            
            if (b == -1)
            {
                b = 9;
                a--;
            }
        }
        
        cur++;
    }
    
    if (cur < dis)
    {
        dis = cur;
        va = a;
        vb = b;
        vc = c;
        vd = d;
    }
}

int main()
{
    yccc;
    int c;
    cin >> c;
    
    while (c--)
    {
        cin >> h >> m;
        cin.get();
        
        dis = INF;
        
        int a, b, c, d;
        
        a = cin.get() - '0';
        b = cin.get() - '0';
        cin.get();
        c = cin.get() - '0';
        d = cin.get() - '0';
        // cout << a << b << c << d << endl;
        
        front(a, b, c, d);
        //back(a, b, c, d);
        
        cout << va << vb << ':' << vc << vd << endl;
    }
}