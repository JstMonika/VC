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

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    while (n--) {
        int f, m, q;
        cin >> f >> m >> q;
        
        vec<pii> File(f);
        for (auto &i : File)
            cin >> i.F >> i.S;
            
        sort(al(File));
        
        vec<pii> available;
        int now = 1;
        for (int i = 0; i < File.size(); i++) {
            if (File[i].F > now) {
                available.emplace_back(now, File[i].F-1);
            }
            
            now = File[i].S+1;
        }
        
        if (now != m+1) available.emplace_back(now, m);
        
        sort(al(available), greater<pii>());
        
        int size = 0;
        vec<pii> ans;
        
        for (auto i : available) {
            if (i.S - i.F + 1 > size) {
                ans.eb(i.S - i.F + 1, i.S);
                size = i.S - i.F + 1;
            }
        }
        
        for (int i = 0; i < q; i++) {
            int need;
            cin >> need;
            
            int ansIdx = -1, L = 0, R = ans.size()-1;
            
            while (L <= R) {
                int M = (L+R) / 2;
                
                if (ans[M].F >= need) {
                    ansIdx = ans[M].S;
                    R = M-1;
                } else
                    L = M+1;
            }
            
            // devec(available);
            
            if (ansIdx == -1)
                cout << "-1 -1\n";
            else
                cout << ansIdx - need + 1 << ' ' << ansIdx << endl;
        }
    }
}