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

const double PI = 3.1415926535;
const double eps = 1e-8;

double _ans = 0, r;
int n;

struct Point {
    double x, y;
    
    Point() {};
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(const Point src) { return Point(src.x+x, src.y+y); }
    Point operator-(const Point src) { return Point(x-src.x, y-src.y); }
    double operator*(const Point src) { return src.x * x + src.y * y; }
    Point operator*(double src) { return Point(x * src, y * src); }
    Point operator/(double src) { return Point(x / src, y / src); }
    double operator^(const Point src) { return x * src.y - y * src.x; }
    
    double dis(const Point src) {
        double dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx * dx + dy * dy);
    }    
};

ostream& operator<<(ostream& stream, const Point src) {
    stream << "(" << src.x << ", " << src.y << ")";
    
    return stream;
}

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double dis(Point src) {
        
        // cout << "distance with: " << src << endl;
        
        double t0 = ((src - sp) * (ep - sp)) / ((ep - sp) * (ep - sp));
        t0 = max(0., min(1., t0));
        // cout << t0 << endl;
        
        // cout << sp << ' ' << ep << endl;
        // cout << sp + (ep-sp) * t0 << endl;
        
        return src.dis(sp + (ep-sp) * t0);
    }
    
    double ori(Point src) { return (ep - sp) ^ (src - sp); }
};

bool inter_with_circle(Line l, Point p, vec<Point>& _list) {
    double B = -(l.ep.x - l.sp.x), A = l.ep.y - l.sp.y;
    
    if (B == 0) {
        if (abs(abs(p.x - l.ep.x) - r) < eps) {
            _list.eb(Point(l.ep.x, p.y));
        } else {
            double dx = l.ep.x - p.x;
            double dy = sqrt(r*r - dx*dx);
            
            _list.eb(Point(l.ep.x, p.y - dy));
            _list.eb(Point(l.ep.x, p.y + dy));
        }
        
        return true;
    } else {
        double C = -(A * l.sp.x + B * l.sp.y);
        
        double dy = -(A * p.x + C) / B;
        C = -B * (dy - p.y);
        
        // cout << l.sp - p << ' ' << l.ep - p << endl;
        // cout << "ABCr: " << A << ' ' << B << ' ' << C << ' ' << r << endl;
        
        double x0 = -A*C/(A*A+B*B) + p.x, y0 = -B*C/(A*A+B*B) + p.y;
        
        // cout << "x, y: " << Point(x0, y0) << endl;
        
        if (C*C > r*r*(A*A+B*B)+eps) return false;
        
        if (abs(C*C - r*r*(A*A+B*B)) < eps) {
            _list.eb(Point(x0, y0));
        } else {
            double d = r*r - C*C/(A*A+B*B);
            double mult = sqrt(d / (A*A+B*B));
            
            _list.eb(Point(x0 + B * mult, y0 - A * mult));
            _list.eb(Point(x0 - B * mult, y0 + A * mult));
        }
        
        return true;
    }
}

struct Query {
    int type;
    Point sp, ep, center;
    
    Query(int type, Line a) : type(type) {
        
        switch (type) {
            case 1: //* right.
                sp = a.sp + Point(0, r);
                ep = a.ep + Point(0, r);
                break;
            case 2: //* down.
                sp = a.sp + Point(r, 0);
                ep = a.ep + Point(r, 0);
                break;
            case 3: //* up.
                sp = a.sp + Point(-r, 0);
                ep = a.ep + Point(-r, 0);
                break;
            case 4: //* rotate down.
                center = a.ep;
                sp = a.ep + Point(0, r);
                ep = a.ep + Point(r, 0);
                break;
            case 5:
                center = a.sp;
                sp = a.sp + Point(-r, 0);
                ep = a.sp + Point(0, r);
                break;
        }
    }
    
    Query() {}
    Query(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    bool intersection(Query src, Point& p) {
        if (type <= 3) {
            if (src.type <= 3) {
                Line a = Line(sp, ep), b = Line(src.sp, src.ep);
                
                // cout << sp << ' ' << ep << "    " << src.sp << ' ' << src.ep << endl;
                // cout << "hi\n";
                
                if (a.ori(src.sp) * a.ori(src.ep) <= 0 and b.ori(sp) * b.ori(ep) <= 0) {
                    
                    bool test = a.ori(src.sp) * a.ori(src.ep) == 0 or b.ori(sp) * b.ori(ep) == 0;
                    
                    if (!test or (src.sp - sp) * (src.sp - ep) < 0 or (src.ep - sp) * (src.ep - ep) < 0) {
                        double t0;
                        
                        t0 = ((sp - src.sp) ^ (src.ep - src.sp)) / ((src.ep - src.sp) ^ (ep - sp));
                        
                        p = sp + (ep - sp) * t0;
                        
                        return true;
                    }
                }
                
                return false;
            } else {
                vec<Point> _list;
                
                if (inter_with_circle(Line(sp, ep), src.center, _list)) {
                    for (int i = 0; i < _list.size(); i++) {
                        double rad = atan2(_list[i].y - src.center.y, _list[i].x - src.center.x);
                        rad += (rad < 0 ? 2 * PI : 0);
                        
                        // cout << sp << ' ' << ep << endl;
                        // cout << _list[i] << " Dis: " << Line(sp, ep).dis(_list[i]) << endl;
                        
                        if (src.type == 4) {
                            // cout << "here!\n";
                            // cout << (rad >= (0 - eps) and rad <= (PI / 2 + eps)) << ' '  << (Line(sp, ep).dis(_list[i]) < eps) << endl;
                            if (rad >= (0 - eps) and rad <= (PI / 2 + eps) and Line(sp, ep).dis(_list[i]) < eps) {
                                p = _list[i];
                                
                                return true;
                            }
                        } else {
                            if (rad >= (PI / 2 - eps) and rad <= (PI + eps) and Line(sp, ep).dis(_list[i]) < eps) {
                                p = _list[i];
                                
                                return true;
                            }
                        }
                    }
                }
                
                return false;
            }
        } else {
            if (src.type <= 3) {
                vec<Point> _list;
                
                if (inter_with_circle(Line(src.sp, src.ep), center, _list)) {
                    for (int i = 0; i < _list.size(); i++) {
                        double rad = atan2(_list[i].y - center.y, _list[i].x - center.x);
                        rad += (rad < 0 ? 2 * PI : 0);
                        
                        // cout << _list[i] << " Dis: " << Line(src.sp, src.ep).dis(_list[i]) << endl;
                        
                        if (type == 4) {
                            // cout << "?\n";
                            if (rad >= (0 - eps) and rad <= (PI / 2 + eps) and Line(src.sp, src.ep).dis(_list[i]) < eps) {
                                p = _list[i];
                                
                                return true;
                            }
                        } else {
                            // cout << rad << ' ' << (PI / 2 - eps) << endl;
                            // cout << (rad >= (PI / 2 - eps * 1000)) << ' ' << (rad <= (PI + eps)) << endl;
                            if (rad >= (PI / 2 - eps) and rad <= (PI + eps) and Line(src.sp, src.ep).dis(_list[i]) < eps) {
                                p = _list[i];
                                
                                return true;
                            }
                        }
                    }
                }
                
                return false;
            } else {
                vec<Point> _list;
                
                double dx = center.x - src.center.x, dy = center.y - src.center.y;
                Point c = (center + src.center) / 2;
                
                // cout << "middle: " << c << ' ' << c + Point(dy, -dx) << endl;
                
                if (inter_with_circle(Line(c, c + Point(dy, -dx)), center, _list)) {
                    for (int i = 0; i < _list.size(); i++) {
                        
                        // cout << "c with c: " << _list[i] << endl;
                        
                        double rad = atan2(_list[i].y - center.y, _list[i].x - center.x);
                        double srcrad = atan2(_list[i].y - src.center.y, _list[i].x - src.center.x);
                        rad += (rad < 0 ? 2 * PI : 0);
                        srcrad += (srcrad < 0 ? 2 * PI : 0);
                        
                        if ((type == 4 and rad >= (0 - eps) and rad <= (PI / 2 + eps)) or (type == 5 and rad >= (PI / 2 - eps) and rad <= (PI + eps)))
                            if ((src.type == 4 and srcrad >= (0 - eps) and srcrad <= (PI / 2 + eps)) or (src.type == 5 and srcrad >= (PI / 2 - eps) and srcrad <= (PI + eps))) {
                                p = _list[i];
                                
                                return true;
                            }
                    }
                }
                
                return false;
            }
        }
    }
    
    double ans() {
        if (type <= 3) {
            return sp.dis(ep);
        } else {
            double sr = atan2(sp.y - center.y, sp.x - center.x);
            sr += (sr < 0 ? 2 * PI : 0);
            double er = atan2(ep.y - center.y, ep.x - center.x);
            er += (er < 0 ? 2 * PI : 0);
            
            return abs(sr - er) * r;
        }
    }
};

ostream& operator<<(ostream& stream, const Query src) {
    
    stream << '[' << src.type << "] ";
    
    if (src.type >= 4) {
        stream << src.center << ", ";
    }
    
    stream << src.sp << ", " << src.ep;
    
    return stream;
}

vec<Line> line;
vec<Query> que;

using pdd = pair<double, double>;

int main()
{
    yccc;
    
    int c = 1;
    
    while (cin >> r >> n) {
        if (n == 0) break;
        
        line.clear();
        que.clear();
        
        _ans = 0;
        
        vec<pdd> _list(n);
        for (auto &i : _list)
            cin >> i.F >> i.S;
        
        double nx = 0, ny = 0;
        
        for (int i = 0; i < n; i++) {
            line.eb(Line(Point(nx, ny), Point(nx + _list[i].F, ny)));
            nx += _list[i].F;
            
            
            if (i != n-1)
                line.eb(Line(Point(nx, ny), Point(nx, ny + _list[i].S)));
            ny += _list[i].S;
        }
        
        for (int i = 0; i < line.size(); i++) {
            // cout << line[i].sp << ' ' << line[i].ep << endl;
            
            if (i % 2) {    //* vertical.
                if (line[i].sp.y > line[i].ep.y) {
                    que.eb(2, line[i]);
                } else {
                    que.eb(3, line[i]);
                    que.eb(5, line[i+1]);
                }
            } else { //* horizontal
                que.eb(Query(1, line[i]));
                
                if (i != line.size()-1 and line[i+1].sp.y > line[i+1].ep.y)
                    que.eb(Query(4, line[i]));
            }
        }
        
        // cout << r << ' ' << n << ' ' << line.size() << ' ' << que.size() << ' ' << _ans << endl;
        // for (auto i : que)
            // cout << i << endl;
        
        bool _good = false;
        int idx = 0;
        
        while (idx != que.size() - 1) {
            _good = false;
            for (int i = que.size()-1; i > idx; i--) {
                Point p;
                
                // cout << "now: " << idx << " and " << i << endl;
                if (que[idx].intersection(que[i], p)) {
                    // cout << "now: " << idx << " and " << i << endl;
                    
                    bool good = true;
                    
                    for (auto k : line) {
                        if (k.dis(p) < r - eps) {
                            good = false;
                            break;
                        }
                    }
                    
                    if (!good)
                        continue;
                    
                    // cout << "\t\t\t" << idx << " and " << i << " at " << p << endl;
                    que[idx].ep = que[i].sp = p;
                    
                    // cout << "plus: " << que[idx].ans() << endl;
                    _ans += que[idx].ans();
                    
                    idx = i;
                    
                    _good = true;
                    break;
                }
            }
            
            if (_good)
                continue;
            
            // cout << "fail\n";
            break;
        }
        
        // cout << "Plus last: " << que[idx].ans() << endl;
        _ans += que[idx].ans();
        
        cout << "Case " << c++ << ": Distance = " << fixed << setprecision(3) << _ans << endl << endl;
    }
}