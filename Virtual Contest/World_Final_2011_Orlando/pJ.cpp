#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-6) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

vec<vec<short>> dp(350, vec<short>(1000001, 1000));
int main()
{
    yccc;
    
    vec<pair<ll, string>> _list;
    ll idx = 2, sum = 5;
    while (sum <= 1000000) {
        _list.eb(sum, to_string(idx) + "H");
        idx++;
        sum += idx * idx;
    }
    
    idx = 3;
    ll oSum = 10, eSum = 4;
    while (oSum <= 1000000 and eSum <= 1000000) {
        if (idx % 2 and oSum <= 1000000) {
            _list.eb(oSum, to_string(idx) + "L");
            
            idx++;
            eSum += idx * idx;
        }
        else if (!(idx % 2) and eSum <= 1000000) {
            _list.eb(eSum, to_string(idx) + "L");
            
            idx++;
            oSum += idx * idx;
        }
    }
    sort(al(_list));

    dp[0][0] = 0;

    for (int i = 1; i <= _list.size(); i++) {
        for (int k = 0; k <= 1000000; k++) {
            if (k-_list[i-1].F >= 0)
                dp[i][k] = min(dp[i-1][k-_list[i-1].F]+1, int(dp[i-1][k]));
            else
                dp[i][k] = min(dp[i][k], dp[i-1][k]);
        }
    }
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        cout << "Case " << c++ << ": ";
        
        if (dp[_list.size()][n] == 1000) {
            cout << "impossible" << endl;
        } else {
            vec<string> ans;
            
            int last = n, idx = _list.size();
            while (idx > 0) {
                if (last-_list[idx-1].F >= 0) {
                    if (dp[idx-1][last-_list[idx-1].F]+1 == dp[idx][last]) {
                        ans.eb(_list[idx-1].S);
                        last -= _list[idx-1].F;
                    }
                }
                
                idx--;
            }
            
            for (int i = 0; i < ans.size(); i++)
                cout << ans[i] << " \n"[i == ans.size()-1];
        }
    }
}