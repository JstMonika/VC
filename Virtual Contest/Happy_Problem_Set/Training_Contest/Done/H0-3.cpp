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

int main()
{
    yccc;
    
    int c; 
    cin >> c;
    
    while (c--) {
        vec<int> _list(4);
        
        string str;
        cin >> str;
        
        int tmp = 0;
        char ch = 0;
        for (int i = 0; i < str.size(); i++) {
            if (isdigit(str[i])) {
                tmp *= 10;
                tmp += str[i] - '0';
            } else {
                if (ch != 0) {
                    if (tmp == 0)
                        tmp = 1;
                        
                    switch (ch) {
                        case 'C':
                            _list[0] += tmp;
                            break;
                        case 'H':
                            _list[1] += tmp;
                            break;
                        case 'O':
                            _list[2] += tmp;
                            break;
                        case 'N':
                            _list[3] += tmp;
                            break;
                    }
                }
                
                ch = str[i];
                tmp = 0;
            }
        }
        
        if (tmp == 0)
            tmp = 1;
        
        switch (ch) {
            case 'C':
                _list[0] += tmp;
                break;
            case 'H':
                _list[1] += tmp;
                break;
            case 'O':
                _list[2] += tmp;
                break;
            case 'N':
                _list[3] += tmp;
                break;
        }
        
        double ans = _list[0] * 12.01 + _list[1] * 1.008 + _list[2] * 16 + _list[3] * 14.01;
        
        cout << fixed << setprecision(3) << ans << endl;
    }
}