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
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        int T;
        vec<int> time(n-1);
        int M1, M2;
        
        cin >> T;
        for (auto &i : time)
            cin >> i;
        
        cin >> M1;
        vec<vec<int>> s(n, vec<int>(M1));
        for (auto &i : s[0])
            cin >> i;
        for (int i = 1; i < n; i++)
            for (int k = 0; k < M1; k++)
                s[i][k] = s[i-1][k] + time[i-1];
        
        cin >> M2;
        vec<vec<int>> e(n, vec<int>(M2));
        for (auto &i : e[n-1])
            cin >> i;
        for (int i = n-2; i >= 0; i--)
            for (int k = 0; k < M2; k++)
                e[i][k] = e[i+1][k] + time[i];
        
        // devec2(s);
        // devec2(e);
        
        vec<vec<int>> dp(T+1, vec<int>(n, INF));
        dp[0][0] = 0;
        
        for (int i = 1; i <= T; i++) {
            for (int k = 0; k < n; k++) {
                dp[i][k] = dp[i-1][k] + 1;
                
                if (k and any_of(al(s[k-1]), [&](int src) { return src == (i - time[k-1]); })) {
                    dp[i][k] = min(dp[i][k], dp[i - time[k-1]][k-1]);
                }
                
                if (k != n-1 and any_of(al(e[k+1]), [&](int src) { return src == (i - time[k]); })) {
                    dp[i][k] = min(dp[i][k], dp[i - time[k]][k+1]);
                }
            }
        }
        
        // devec2(dp);
        
        cout << "Case Number " << c++ << ": " << (dp[T][n-1] >= INF ? "impossible\n" : to_string(dp[T][n-1]) + "\n");
    }
}