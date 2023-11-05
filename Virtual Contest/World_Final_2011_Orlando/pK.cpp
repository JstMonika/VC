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
    
    Point operator*(double t) {
        return Point(t * x, t * y);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
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
    
    double dis(Point p) {
        double t = ((p-sp) * (ep-sp)) / ((ep-sp) * (ep-sp));
        
        return p.dis(sp + (ep-sp) * t);
    }
    
    double ori(Point p) {
        return (ep-sp) ^ (p-sp);
    }
};

struct Polygon {
    vec<Point> p;
    
    Polygon() {}
    Polygon(vec<Point> p) : p(p) {}
    
    void convex() {
        auto cmp = [](Point p1, Point p2) -> bool {
            if (p1.x != p2.x)
                return p1.x < p2.x;
            return p1.y < p2.y;
        };
        sort(al(p), cmp);
        
        vec<Point> hull;
        for (int i = 0; i < 2; i++) {
            auto start = hull.size();
            for (auto k : p) {
                while (hull.size() >= start + 2 and Line(hull[hull.size()-2], hull.back()).ori(k) <= 0) hull.pop_back();
                hull.eb(k);
            }
            
            hull.pop_back();
            reverse(al(p));
        }
        
        p = hull;
    }
};

int next(int i, int n) {
    return (i+1) % n;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        vec<Point> _list(n);
        for (auto &i : _list)
            cin >> i.x >> i.y;
            
        Polygon hull(_list);
        hull.convex();
        
        double ans = INF;
        int s = hull.p.size(), idx = 1;
        for (int i = 0; i < hull.p.size(); i++) {
            while (Line(hull.p[i], hull.p[next(i, s)]).dis(hull.p[idx]) < Line(hull.p[i], hull.p[next(i, s)]).dis(hull.p[next(idx, s)])) idx = next(idx, s);
            ans = min(ans, Line(hull.p[i], hull.p[next(i, s)]).dis(hull.p[idx]));
        }
        
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << ceil(ans*100)/100 << endl;
    }
}