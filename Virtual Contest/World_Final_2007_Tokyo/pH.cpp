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

#define point(v) "(" << v.x << ", " << v.y << ", " << v.z << ")"

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

int n, v;

struct Point {
    double x, y, z;
    
    Point() {}
    Point(double x, double y, double z) : x(x), y(y), z(z) {}
    
    bool operator<(Point p) const {
        if (x != p.x)
            return x < p.x;
        // if (y != p.y)
            return y < p.y;
        return y < p.z;
    }
    
    bool operator==(Point p) const {
        return fcmp(x, p.x) == 0 && fcmp(y, p.y) == 0;
    }
    
    bool operator!=(Point p) const {
        return !(*this == p);
    }
    
    Point operator+(Point p) {
        return Point(x + p.x, y + p.y, z + p.z);
    }
    
    Point operator-(Point p) {
        return Point(x - p.x, y - p.y, z - p.z);
    }
    
    Point operator*(double src) {
        return Point(x * src, y * src, z * src);
    }
    
    Point operator/(double src) {
        return Point(x / src, y / src, z / src);
    }
    
    double operator*(Point p) {
        return p.x * x + p.y * y;
    }
    
    double operator^(Point p) {
        return x * p.y - y * p.x;
    }
    
    double dis(Point src, int level) {
        double dx = x - src.x, dy = y - src.y, dz = z - src.z;
        
        if (level == 2)
            return sqrt(dx * dx + dy * dy);
        
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};

istream& operator>>(istream& in, Point& src) {
    in >> src.x >> src.y >> src.z;
    
    return in;
}

ostream& operator<<(ostream& out, Point& src) {
    out << src.x << ' ' << src.y << ' ' << src.z;
    
    return out;
}

vec<Point> vertex;
vec<double> xList;

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point s, Point e) : sp(s), ep(e) {
        if (ep < sp)
            swap(sp, ep);
    }
    
    bool operator<(Line src) const {
        if (sp != src.sp)
            return sp < src.sp;
        return ep < src.ep;
    }
    
    bool operator!=(Line src) const {
        return sp != src.sp or ep != src.ep;
    }
    
    pair<bool, Point> intersect(Line src) {
        if (ori(src.sp) * ori(src.ep) < 0 and src.ori(sp) * src.ori(ep) < 0) {
            double t = ((src.ep - src.sp) ^ (sp - src.sp)) / ((ep - sp) ^ (src.ep - src.sp));
            
            return {true, sp + (ep-sp) * t};
        }
        
        return {false, Point()};
    }
    
    double ori(Point src) {
        return (ep-sp) ^ (src-sp);
    }
};

ostream& operator<<(ostream& out, Line src) {
    out << src.sp << " <-> " << src.ep;
    
    return out;
}

struct Tri {
    vec<Point> v;
    vec<Line> e;
    double scale;
    
    Tri() { 
        v.resize(3); 
        e.resize(3); 
        scale = 1;
    }
    
    Tri(int a, int b, int c) {
        v.resize(3);
        v[0] = vertex[a-1];
        v[1] = vertex[b-1];
        v[2] = vertex[c-1];
        
        e.resize(3);
        e[0] = Line(v[0], v[1]);
        e[1] = Line(v[1], v[2]);
        e[2] = Line(v[2], v[0]);
        
        double A = v[0].dis(v[1], 3), B = v[1].dis(v[2], 3), C = v[2].dis(v[0], 3), R = (A+B+C) / 2;
        double sA = v[0].dis(v[1], 2), sB = v[1].dis(v[2], 2), sC = v[2].dis(v[0], 2), sR = (sA+sB+sC) / 2;
        
        double origin_dis = sqrt(R * (R-A) * (R-B) * (R-C)), scale_dis = sqrt(sR * (sR-sA) * (sR-sB) * (sR-sC));
        // cout << "scale: " << origin_dis << " " << scale_dis << endl;
        scale = (scale_dis == 0 ? 0 : origin_dis / scale_dis);
    }
    
    double find_z(double x, double y) {
        Point fv = v[1] - v[0], sv = v[2] - v[0];
        
        Point plane(fv.y*sv.z - sv.y*fv.z, fv.z*sv.x - sv.z*fv.x, fv.x*sv.y - sv.x*fv.y);
        
        return (plane.x * (x - v[0].x) + plane.y * (y - v[0].y)) / -plane.z + v[0].z;
        // TODO.
        return -1;
    }
    
    double find_z(Point src) {
        Point fv = v[1] - v[0], sv = v[2] - v[0];
        
        Point plane(fv.y*sv.z - sv.y*fv.z, fv.z*sv.x - sv.z*fv.x, fv.x*sv.y - sv.x*fv.y);
        
        return (plane.x * (src.x - v[0].x) + plane.y * (src.y - v[0].y)) / -plane.z + v[0].z;
        // TODO.
        return -1;
    }
};

ostream& operator<<(ostream& out, Tri src) {
    cout << "Polygon(" << point(src.v[0]) << ", " << point(src.v[1]) << ", " << point(src.v[2]) << ")" << endl;
    cout << src.scale;
    
    return out;
}

vec<Tri> _list;

pair<bool, Line> check(Line src, double left, double right) {
    
    Point d = src.ep - src.sp;
    // debug(d);
    // debug(src.sp);
    // debug(src.ep);
    double leftScale = (left - src.sp.x) / d.x, rightScale = (right - src.sp.x) / d.x;
    // cout << leftScale << " " << rightScale << endl;
    Point l = src.sp + d * leftScale, r = src.sp + d * rightScale;
    // debug(l);
    // debug(r);
    
    if (src.sp.x <= left and src.ep.x >= right)
        return {true, Line(l, r)};
    
    return {false, Line()};
}

int next(int i, int n) {
    return (i+1) % n;
}

bool isin(Point src, Tri triangle) {
    // cout << "Point: " << src << endl;
    vec<double> sign(3);
    
    if (triangle.e[0].ep != triangle.e[1].sp and triangle.e[0].ep != triangle.e[1].ep)
        swap(triangle.e[0].sp, triangle.e[0].ep);
    
    for (int i = 0; i < 3; i++) {
        if (i and triangle.e[i].sp != triangle.e[i-1].ep)
            swap(triangle.e[i].sp, triangle.e[i].ep);
        
        // cout << triangle.e[i].sp << " " << triangle.e[i].ep << endl;
        sign[i] = triangle.e[i].ori(src);
    }
    // cout << src << endl;
    
    // devec(sign);
    
    for (int i = 0; i < 3; i++) {
        if (fcmp(sign[i] * sign[next(i, 3)], 0) < 0) {
            
            return false;
        }
    }
    
    return true;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> v >> n) {
        if (!n) break;
        
        vertex.resize(v);
        _list.resize(n);
        xList.clear();
        
        for (auto &i : vertex)
            cin >> i;
        for (auto &i : _list) {
            int r, s, t;
            cin >> r >> s >> t;
            
            i = Tri(r, s, t);
            
            xList.eb(vertex[r-1].x);
            xList.eb(vertex[s-1].x);
            xList.eb(vertex[t-1].x);
            
            //dbg
            // cout << i << endl;
        }
        
        for (int i = 0; i < n; i++)
            for (int k = i+1; k < n; k++)
                for (int ti = 0; ti < 3; ti++)
                    for (int tk = 0; tk < 3; tk++) {
                        bool good;
                        Point ret;
                        tie(good, ret) = _list[i].e[ti].intersect(_list[k].e[tk]);
                        
                        if (good) {
                            xList.eb(ret.x);
                        }
                    }
        
        sort(al(xList));
        xList.resize(distance(xList.begin(), unique(al(xList))));
        
        // devec(xList);
        
        vec<vec<Line>> Segment(n);
        double ans = 0.0;
        
        // debug(xList.size())
        
        for (int i = 0; i < xList.size() - 1; i++) {
            vec<vec<Line>> Segment(n);
            //* cut all edges in this slice
            vec<pair<Line, int>> segList;
            
            for (int k = 0; k < _list.size(); k++) {
                for (int tk = 0; tk < 3; tk++) {
                    // debug(_list[k].e[tk]);
                    // debug(xList[i]);
                    // debug(xList[i+1]);
                    auto ret = check(_list[k].e[tk], xList[i], xList[i+1]);
                    // debug(ret.F);
                    
                    if (ret.F) {
                        segList.eb(ret.S, k);
                        Segment[k].eb(ret.S);
                        // cout << k << " push " << ret.S.sp << " to " << ret.S.ep << endl;
                    }
                }
            }
            
            sort(al(segList));
            
            //dbg
            // for (auto k : segList)
            //     cout << point(k.F.sp) << ", " << point(k.F.ep) << ' ' << k.S << endl;
            // vec<double> nowX = {xList[i], xList[i+1]};
            
            set<int> _set;
            deq<bool> vis(n);
            
            //dbg
            // cout << "--------------\n";
            // cout << xList[i] << " to " << xList[i+1] << ":\n";
            
            auto prev = pair<Line, int>(Line(), -1);
            
            vec<double> sum(n);
            for (auto k : segList) {
                if (!_set.empty()) {
                    //* four point:
                    //* k.sp, k.ep
                    //* prev.sp, prev.ep
                    
                    int now = -1;
                    double max = -INF;
                    for (auto z : _set) {
                        double val = _list[z].find_z(k.F.sp)
                                   + _list[z].find_z(k.F.ep)
                                   + _list[z].find_z(prev.F.sp)
                                   + _list[z].find_z(prev.F.ep);
                        
                        if (val > max) {
                            max = val;
                            now = z;
                        }
                    }
                    
                    //dbg
                    // cout << point(prev.F.sp) << ' ' << point(prev.F.ep) << endl;
                    // cout << point(k.F.sp) << ' ' << point(k.F.ep) << endl;
                    // cout << "-------> " << now << ' ' << (((k.F.sp.y - prev.F.sp.y) + (k.F.ep.y - prev.F.ep.y)) * (xList[i+1] - xList[i]) / 2) << endl;
                    
                    if (now != -1) {
                        sum[now] += (((k.F.sp.y - prev.F.sp.y) + (k.F.ep.y - prev.F.ep.y)) * (xList[i+1] - xList[i]) / 2);
                        
                        ans += (((k.F.sp.y - prev.F.sp.y) + (k.F.ep.y - prev.F.ep.y)) * (xList[i+1] - xList[i]) / 2) * _list[now].scale;
                    }
                    //* find area.
                }
                
                prev = k;
                
                if (vis[k.S]) {
                    // cout << "erase " << k.S << endl;
                    _set.erase(k.S);
                    
                    vis[k.S] = false;
                }
                else {
                    // cout << "emplace " << k.S << endl;
                    _set.emplace(k.S);
                    
                    vis[k.S] = true;
                }
                
                // cout << "set size: " << _set.size() << endl;
            }
            
            //dbg
            // cout << xList[i] << " to " << xList[i+1] << ":\n";
            // cout << "total:\n";
            // for (int k = 0; k < n; k++) 
            //     if (sum[k] != 0) cout << k << ": " << sum[k] << endl;
        }
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << ans << endl << endl;
    }
}