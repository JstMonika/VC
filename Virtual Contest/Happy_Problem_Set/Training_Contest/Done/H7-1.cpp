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

struct Color {
    int num, idx, color;
    
    Color() {}
    Color(int n, int i, int c) : num(n), idx(i), color(c) {}
};

bool operator<(Color a, Color b) {
    return a.num < b.num;
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n, k;
        cin >> n >> k;
        
        vec<int> _list(n);
        REP(i, n) {
            cin >> _list[i];
        }
        
        auto tmp = _list;
        sort(al(tmp));
        
        tmp.resize(unique(al(tmp)) - tmp.begin());
        
        vec<Color> paint(n);
        REP(i, n) {
            paint[i].num = lower_bound(al(tmp), _list[i]) - tmp.begin();
            paint[i].idx = i;
            
            _list[i] = paint[i].num;
        }
        
        sort(al(paint));
        
        // REP(i, paint.size())
        //     cout << paint[i].num << ' ';
        // cout << endl;
        
        vec<int> much(tmp.size());
        int much_num = 0;
        for (int i = 0; i < tmp.size(); i++) {
            if (upper_bound(al(paint), Color(i, 0, 0)) - lower_bound(al(paint), Color(i, 0, 0)) >= k) {
                much_num += upper_bound(al(paint), Color(i, 0, 0)) - lower_bound(al(paint), Color(i, 0, 0));
                much[i] = k;
            } else {
                much[i] = -1;
            }
        }
        
        int _num = (paint.size() - much_num) / k * k, idx = 0;
        for (int i = 0; i < paint.size(); i++) {
            if (much[paint[i].num] == -1) {
                if (_num-- > 0) {
                    paint[i].color = idx % k + 1;
                    idx++;
                } else {
                    paint[i].color = 0;
                }
            } else {
                paint[i].color = much[paint[i].num];
                
                if (much[paint[i].num] != 0)
                    much[paint[i].num]--;
            }
        }
        
        auto cmp = [](Color a, Color b) { return a.idx < b.idx; };
        sort(al(paint), cmp);
        
        // devec(much);
        // REP(i, paint.size())
        //     cout << paint[i].num << ' ';
        // cout << endl;
        
        for (int i = 0; i < paint.size(); i++) {
            cout << paint[i].color << " \n"[i == _list.size()-1];
        }
    }
}