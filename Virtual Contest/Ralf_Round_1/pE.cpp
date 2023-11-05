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

int cont[100001];
int main()
{
    yccc;
    int n, k;
    cin >> n >> k;
    vec<ll> _list(n);
    double aver = 0;
    ll sum = 0;
    
    for (auto &i : _list)
    {
        cin >> i;
        aver += i;
    }
    aver /= k;
    sort(al(_list));
    int idx = 0;
    while (_list[idx] <= aver)
    {
        sum += _list[idx] * _list[idx];
        idx++;
    }
    
    int last = k-n-idx;
    for (int i = _list.size() - 1; i >= idx; i--)
    {
        if (last == 0)
        {
            sum += _list[i] * _list[i];
            continue;
        }
        
        int piece = ceil(1.0 * _list[i] / aver);
        if (piece < last)
        {
            sum += (_list[i] / piece) * (_list[i] / piece) * (piece-1);
            sum += (_list[i] / piece + _list[i] % piece) * (_list[i] / piece + _list[i] % piece);
            last -= piece;
        }
        else
        {
            if (_list[i] % last)
            {
                sum += (_list[i] / last) * (_list[i] / last) * (last-1);
                sum += (_list[i] / last + _list[i] % last) * (_list[i] / last + _list[i] % last);
                last = 0;
            }
            else
            {
                sum += (_list[i] / last) * (_list[i] / last) * last;
                last = 0;
            }
            
        }
    }
    
    cout << sum << endl;
}