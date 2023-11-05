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

struct Point {
    ll x, y;
    Point() {}
    Point(ll x, ll y) : x(x), y(y) {}
    
    bool operator<(Point& src) {
        if (x != src.x) return x < src.x;
        return y < src.y;
    }
    
    Point operator-(Point& src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    bool operator!=(Point src) const {
        return x != src.x or y != src.y;
    }
};

struct Line {
    Point sp, ep;
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    ll ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
};

vec<Point> hull;

int next(int i, int s, int n = 1) {
    return (i + n) % s;
}

ll area(int i, int k, int n) {
    return abs((hull[i] - hull[k]) ^ (hull[i] - hull[n]));
}

ll area(Point i, Point k, Point n) {   
    return abs((i - k) ^ (i - n));
}

ll ans;

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        ans = 0;
        
        int n;
        cin >> n;
        
        vec<Point> _list(n);
        for (auto &i : _list)
            cin >> i.x >> i.y;
            
        sort(al(_list));
        
        hull.clear();
        for (int i = 0; i < 2; i++) {
            auto s = hull.size();
            
            for (auto &i : _list) {
                while (hull.size() >= s + 2 and Line(hull[hull.size() - 2], hull.back()).ori(i) < 0)
                    hull.pop_back();
                    
                hull.eb(i);
            }
            
            hull.pop_back();
            reverse(al(_list));
        }
        
        int _s = hull.size();
        
        if (_s < 3) cout << 0 << endl;
        else if (_s == 3) {
            for (auto i : _list) {
                if (i != hull[0] and i != hull[1] and i != hull[2]) {
                    ll sum = area(hull[0], hull[1], hull[2]);
                    
                    ans = max(ans, sum - min({area(hull[0], i, hull[1]), area(hull[1], i, hull[2]), area(hull[2], i, hull[0])}));
                }
            }
        } else {
            for (int i = 0; i < _s; i++) {
                int p1 = next(i, _s), p2 = next(i, _s, 3);
                for (int k = next(i, _s, 2); next(k, _s) != i; k = next(k, _s)) {
                    while (next(p1, _s) != k and area(i, p1, k) < area(i, next(p1, _s), k)) p1 = next(p1, _s);
                    while (next(p2, _s) != i and area(i, p2, k) < area(i, next(p2, _s), k)) p2 = next(p2, _s);
                    
                    ans = max(ans, area(i, p1, k) + area(i, p2, k));
                }
            }
        }
        
        cout << ans / 2;
        if (ans % 2) cout << ".5";
        
        cout << endl;
    }
}