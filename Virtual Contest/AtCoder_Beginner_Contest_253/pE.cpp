#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

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

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 998244353;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int n, m, K;
    cin >> n >> m >> K;
    
    vec<vec<ll>> dp(n+1, vec<ll>(m+1));
    vec<ll> pre(m+1);
    
    for (int k = 1; k <= m; k++) dp[2][k] = max(0, k - K) + max(0, m - k - K + 1) - (K == 0 ? 1 : 0);
    
    for (int i = 3; i <= n; i++) {
        for (int k = 1; k <= m; k++) (pre[k] = pre[k-1] + dp[i-1][k]) %= MOD;
        
        for (int k = 1; k <= m; k++) {
            (dp[i][k] = (pre[max(0, k-K)] - pre[0]) + (pre[m] - pre[min(m, k+K-1)]) - (K == 0 ? dp[i-1][k] : 0)) %= MOD;
            // cout << (pre[max(0, k-K)] - pre[0]) << ' ' << (pre[m] - pre[min(m, k+K-1)]) << ' ' << (K == 0 ? dp[i-1][k] : 0) << ' ' << dp[i][k] << endl;
        }
    }
    
    // devec2(dp);
    
    ll ans = 0;
    for (int k = 1; k <= m; k++) (ans += dp[n][k]) %= MOD;
    cout << (ans < 0 ? ans + MOD : ans);
}