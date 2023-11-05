#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<typename T> using vec = vector<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
// const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

const ll _MOD = 998244353;

ll pow(ll a, ll b, ll MOD) {
    ll ret = 1;
    
    a %= MOD;
    do {
        if (b & 1) {
            ret *= a;
            ret %= MOD;
        }
        
        a *= a;
        a %= MOD;
    } while (b >>= 1);
    
    return ret;
}

int main()
{
    yccc;
    
    ll n, k, m;
    cin >> n >> k >> m;
    
    //* output m^(k^n)
    //* equal to 
    
    cout << (m % _MOD ? pow(m, pow(k, n, _MOD-1), _MOD) : 0);
}