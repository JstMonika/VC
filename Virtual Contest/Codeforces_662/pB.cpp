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
void mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; }
void tmod(ll& a, ll b) { a = (a*b) % MOD; }
ll POW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }

int main()
{
    int n, two = 0, four = 0;
    cin >> n;
    map<int, int> mp;
    
    REP(i, n)
    {
        int tmp;
        cin >> tmp;
        
        mp[tmp]++;
        
        if (mp[tmp] == 2)
            two++;
        else if (mp[tmp] == 4)
        {
            two--;
            four++;
        }
        else if (mp[tmp] == 6)
            two++;
        else if (mp[tmp] == 8)
        {
            two--;
            four++;
        }
    }
    
    int t;
    cin >> t;
    cin.get();
    
    REP(i, t)
    {
        char ch;
        int tn;
        cin >> ch >> tn;
        
        if (ch == '+')
        {
            mp[tn]++;
            
            if (mp[tn] == 2)
                two++;
            else if (mp[tn] == 4)
            {
                two--;
                four++;
            }
            else if (mp[tn] == 6)
                two++;
            else if (mp[tn] == 8)
            {
                two--;
                four++;
            }
        }
        else
        {
            mp[tn]--;
            
            if (mp[tn] == 7)
            {
                four--;
                two++;
            }
            else if (mp[tn] == 5)
                two--; 
            else if (mp[tn] == 3)
            {
                two++;
                four--;
            }
            else if (mp[tn] == 1)
                two--;
        }
        
        if (four >= 2 or (four and two >= 2))
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}