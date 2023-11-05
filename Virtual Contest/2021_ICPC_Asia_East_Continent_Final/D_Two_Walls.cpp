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

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-6) {
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
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator*(Point src) {
        return x * src.x + y * src.y;
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
};

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep-sp) ^ (src-sp);
    }
    
    bool intersect(Line src) {
        double _sp = src.ori(sp);
        double _ep = src.ori(ep);
        double s_sp = ori(src.sp);
        double s_ep = ori(src.ep);
        
        if (fcmp(_sp, 0) == 0 and fcmp(_ep, 0) == 0)
            return src.isPointOnSegment(sp) or src.isPointOnSegment(ep) or isPointOnSegment(src.sp) or isPointOnSegment(src.ep);
        
        return (ori(src.sp) * ori(src.ep) < 0) and (src.ori(sp) * src.ori(ep) < 0);
    }
    
    bool isPointOnSegment(Point src) {
        return fcmp(ori(src)) == 0 and ((src-ep) * (src-sp) < 0);
    }
};

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        vec<Point> P(2);
        vec<Line> _list(2);
        
        cin >> P[0].x >> P[0].y >> P[1].x >> P[1].y;
        for (int i = 0; i < 2; i++) {
            cin >> _list[i].sp.x >> _list[i].sp.y >> _list[i].ep.x >> _list[i].ep.y;
        }
        
        vec<deq<bool>> test(2, deq<bool>(4));
        
        for (int i = 0; i < 2; i++) {
            test[i][0] = !(Line(P[i], _list[0].sp).intersect(_list[1]) or Line(P[i], _list[0].sp).isPointOnSegment(_list[0].ep));
            test[i][1] = !(Line(P[i], _list[0].ep).intersect(_list[1]) or Line(P[i], _list[0].ep).isPointOnSegment(_list[0].sp));
            test[i][2] = !(Line(P[i], _list[1].sp).intersect(_list[0]) or Line(P[i], _list[1].sp).isPointOnSegment(_list[1].ep));
            test[i][3] = !(Line(P[i], _list[1].ep).intersect(_list[0]) or Line(P[i], _list[1].ep).isPointOnSegment(_list[1].sp));
        }
        
        if (!Line(P[0], P[1]).intersect(_list[0]) and !Line(P[0], P[1]).intersect(_list[1]))
            cout << 0 << endl;
        else {
            bool good = false;
            
            for (int i = 0; i < 4; i++) {
                if (test[0][i] and test[1][i])
                    good = true;
            }
            
            cout << (good ? 1 : 2) << endl;
        }
        
        devec2(test);
    }
}