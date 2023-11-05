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

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

void pmod(ll& a, ll b) { a = (a+b) % MOD; }
void pmod(ll& a, ll b, ll c) { a = (a+b) % c; }
void mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; }
void tmod(ll& a, ll b) { a = (a*b) % MOD; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }

int main()
{
    int c;
    cin >> c;
    
    while (c--)
    {
        int n;
        cin >> n;
        
        map<int, int> mp;
        
        REP(i, n)
        {
            int tmp;
            cin >> tmp;
            
            mp[tmp]++;
        }
        
        vec<int> num;
        for (auto [a, b] : mp)
            num.eb(b);
            
        sort(al(num), greater<int>());
        
        ll idx = 0, dis = INF;
        vec<ll> index(num.size());
        REP(i, num.size())
            index.at(i) = -1;
        
        for (int i = 0; i < n; i++)
        {
            num.at(idx)--;
            
            if (index.at(idx) != -1)
                dis = min(dis, i - index.at(idx) - 1);
            index.at(idx) = i;
            
            pmod(idx, 1, num.size());
            
            if (num.at(idx) == 0)
                idx = 0;
        }
        
        cout << dis << endl;
    }
}