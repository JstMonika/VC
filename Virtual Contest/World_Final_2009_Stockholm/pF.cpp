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
    double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator*(Point src) {
        return x * src.x + y * src.y;
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    bool operator<(Point src) {
        if (x != src.x)
            return x < src.x;
        return y < src.y;
    }
    
    bool operator==(Point src) {
        return x == src.x && y == src.y;
    }
    
    double dis(Point src) {
        double dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx * dx + dy * dy);
    }
};

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
};

deq<bool> sel(9);
vec<int> nxt;
void subset(int i, int now) {
    if (now == 9) {
        int num = 0;
        for (int k = 0; k < 9; k++)
            num += (sel[k] ? (1<<k) : 0);
        
        if (i != num) 
            nxt.eb(num);
            
        return;
    }
    
    if (i & (1<<now)) {
        sel[now] = true;
        subset(i, now+1);
        sel[now] = false;
    }
    
    subset(i, now+1);
}

int next(int i, int n) {
    return (i+1) % n;
}

int n, m;
vec<Point> _list;
double cal(int i) {
    vec<Point> P;
    for (int k = 0; k < 9; k++)
        if (i & (1<<k)) P.eb(_list[k]);
        
    sort(al(P));
    
    // debug(P.size());
    
    vec<Point> hull;
    for (int z = 0; z < 2; z++) {
        auto start = hull.size();
        for (auto point : P) {
            while (hull.size() >= start + 2 and
                   Line(hull[hull.size()-2], hull.back()).ori(point) <= 0)
                hull.pop_back();
            hull.eb(point);
        }
        hull.pop_back();
        
        reverse(al(P));
    }
    
    if (hull.size() == 2 and hull[0] == hull[1])
        hull.pop_back();
        
    // debug(hull.size());
    // for (auto point : hull)
    //     cout << point.x << ' ' << point.y << endl;
        
    double ans = 0;
    for (int k = 0; k < hull.size(); k++)
        ans += hull[k].dis(hull[next(k, hull.size())]);
    
    ans += m * 2 * PI;
    
    // debug(ans);
    
    return ans;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        _list.resize(n);
        for (auto &i : _list)
            cin >> i.x >> i.y;
            
        vec<double> dp(1<<n, llINF);
        dp[0] = 0;
        
        for (int i = 1; i < (1<<n); i++) {
            nxt.clear();
            subset(i, 0);
            
            for (auto k : nxt) {
                // cout << i << ' ' << k << ' ' << cal(i-k) << endl;
                dp[i] = min(dp[i], dp[k] + cal(i-k));   
            }
        }
        
        // devec(dp);
        
        cout << "Case " << c++ << ": length = " << fixed << setprecision(2) << dp[(1<<n)-1] << endl;
    }
}