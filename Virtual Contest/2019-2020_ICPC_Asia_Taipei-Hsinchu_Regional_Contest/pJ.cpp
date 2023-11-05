#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 0x3f3f3f3f;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        int ans = 20;
        
        int n, m;
        cin >> n >> m;
        
        vec<bitset<505>> dp(1<<m);
        for (int i = 0; i < m; i++) {
            string str;
            cin >> str;
            
            dp[1<<i] = bitset<505>(str);
        }
        
        for (int i = 1; i < (1<<m); i++) {
            for (int k = 0; k < m; k++) {
                if (i & (1<<k))
                    dp[i] |= dp[1<<k];
            }
            if (dp[i].count() == n) {
                ans = min(ans, __builtin_popcount(i));
            }
        }
        
        cout << (ans == 20 ? -1 : ans) << endl;
    }
}