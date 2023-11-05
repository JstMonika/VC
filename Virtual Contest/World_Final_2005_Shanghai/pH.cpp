#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Point {
    int x, y;
    
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
};

int n, ans;
vec<p<int>> init, finish;

int step(int i, int k) {
    return abs(init[i].F - finish[k].F) + abs(init[i].S - finish[k].S);
}

void solve() {
    vec<int> dp(1<<n, INF);
    dp[0] = 0;
    
    for (int i = 0; i < n; i++) {
        string str = string(n-i, '0') + string(i, '1');
        
        do {
            int base = 1, num = 0;
            for (int k = str.size() - 1; k >= 0; k--) {
                num += (str[k] == '1') * base;
                base *= 2;
            }
            
            // cout << num << ' ' << str << endl;
            
            for (int k = 0; k < n; k++) {
                if (!(num & (1<<k))) {
                    // cout << (num | (1 << k)) << endl;
                    dp[num | (1<<k)] = min(dp[num | (1<<k)], dp[num] + step(i, k));
                }
            }
            
        } while (next_permutation(al(str)));
    }
    
    // cout << (1<<n) - 1 << endl;
    // cout << dp[(1<<n)-1] << endl;
    
    ans = min(dp[(1<<n)-1], ans);
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n) {
        if (!n) break;
        
        ans = INF;
        
        init.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> init[i].F >> init[i].S;
            init[i].F--, init[i].S--;
        }
        
        finish.resize(n);
        for(int i = 0; i < n; i++) {   
            for (int k = 0; k < n; k++)
                finish[k].F = i, finish[k].S = k;
            solve();
            
            for (int k = 0; k < n; k++)
                finish[k].S = i, finish[k].F = k;
            solve();
            
        }
            
        
        for (int i = 0; i < n; i++)
            finish[i].F = finish[i].S = i;
        
        // cout << "dia\n";
        solve();
        
        for (int i = 0; i < n; i++)
            finish[i].F = i, finish[i].S = n-1-i;
        
        // cout << "dia\n";
        solve();
        
        cout << "Board " << c++ << ": " << ans << " moves required.\n\n";
    }
}