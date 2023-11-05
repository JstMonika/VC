#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

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

struct Point {
    int x, y;
    
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    double dis(Point src) {
        int dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx * dx + dy * dy);
    }
};

#define gt(x, v) get<v>(x)
using Node = tuple<double, int, int, int>;

vec<vec<vec<Node>>> dp(300, vec<vec<Node>>(2, vec<Node>(300, Node(INF, -1, -1, -1))));

int main()
{
    yccc;
    
    int n, s1, s2, c = 1;
    while (cin >> n >> s1 >> s2) {
        if (!n) break;
        
        vec<Point> _list(n);
        for (auto &i : _list)
            cin >> i.x >> i.y;
        
        if (s1 > s2) swap(s1, s2);
        
        for (int i = 0; i < 300; i++)
            for (int k = 0; k < 2; k++)
                fill(al(dp[i][k]), Node(INF, -1, -1, -1));
        
        if (s1 != 1)
            gt(dp[1][0][0], 0) = gt(dp[1][1][0], 0) = _list[0].dis(_list[1]);
        else
            gt(dp[1][0][0], 0) = _list[0].dis(_list[1]);
        
        for (int i = 2; i < n; i++) {
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < 2; k++) {
                    if (i == s1 and k == 1) continue;
                    if (i == s2 and k == 0) continue;
                    
                    if (j == i-1) {
                        for (int r = 0; r <= i-2; r++)
                            if (gt(dp[i-1][1-k][r], 0) + _list[i].dis(_list[r]) < gt(dp[i][k][j], 0)) {
                                gt(dp[i][k][j], 0) = gt(dp[i-1][1-k][r], 0) + _list[i].dis(_list[r]);
                                
                                gt(dp[i][k][j], 1) = i-1;
                                gt(dp[i][k][j], 2) = 1-k;
                                gt(dp[i][k][j], 3) = r;
                            }
                    } else {
                        gt(dp[i][k][j], 0) = gt(dp[i-1][k][j], 0) + _list[i].dis(_list[i-1]);
                        
                        gt(dp[i][k][j], 1) = i-1;
                        gt(dp[i][k][j], 2) = k;
                        gt(dp[i][k][j], 3) = j;
                    }
                
                    // cout << i << ' ' << k << ' ' << j << ' ' << gt(dp[i][k][j], 0) << endl;
                }
            }
        }
        
        double ans = INF;
        vec<int> p1, p2;
        for (int k = 0; k < 2; k++) {
            for (int j = 0; j < n-1; j++) {
                
                if (gt(dp[n-1][k][j], 0) + _list[n-1].dis(_list[j]) < ans) {
                    ans = min(ans, gt(dp[n-1][k][j], 0) + _list[n-1].dis(_list[j]));
                    
                    p1.clear();
                    p2.clear();
                    
                    double tmp;
                    int pi = n-1, pk = k, pj = j;
                    do {
                        if (pk) p2.eb(pi);
                        else p1.eb(pi);
                        
                        tie(tmp, pi, pk, pj) = dp[pi][pk][pj];
                        // cout << pi << ' ' << pk << ' ' << pj << endl;
                    } while (pi != -1);
                }
            }
        }
        
        reverse(al(p1));
        reverse(al(p2));
        // devec(p1);
        // devec(p2);
        
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << ans << endl;
        cout << 0;
        
        if (p1.size() and p1[0] == 1) {
            reverse(al(p2));
            for (auto i : p1) cout << ' ' << i;
            for (auto i : p2) cout << ' ' << i;
        } else {
            reverse(al(p1));
            for (auto i : p2) cout << ' ' << i;
            for (auto i : p1) cout << ' ' << i;
        }
        
        cout << ' ' << 0 << endl;
    }
}