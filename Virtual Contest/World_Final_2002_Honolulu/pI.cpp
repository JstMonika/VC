#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<double, double>;
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
const double eps = 1e-9;
const double EPS = 1e-5;

double r;
int n, nxt;

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
    
    Point operator*(double src) {
        return Point(x * src, y * src);
    }
    
    Point operator/(double src) {
        return Point(x / src, y / src);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    double dis(Point src) {
        double dx = x - src.x, dy = y - src.y;
        return sqrt(dx*dx + dy*dy);
    }
};

struct Line {
    Point sp, ep;
    
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep-sp) ^ (src-sp);
    }
    
    double dis(Point src) {
        double _t = ((src - sp) * (ep - sp)) / ((ep - sp) * (ep - sp));
        
        _t = max(0., min(1., _t));
        
        return src.dis((ep-sp) * _t + sp);
    }
};

inline bool isin(double src, int type) {
    // cout << type << endl;
    // cout << "tan: " << src << endl;
    // cout << "PI/2: " << PI/2 << endl;
    // cout << (src >= 0 and src <= PI/2 + EPS) << endl;
    // cout << "-----\n";
    if (src < 0) src += 2 * PI;
    
    if (type == 4)
        return src >= (0 - EPS) and src <= (PI/2 + EPS);
    
    // cout << src << endl;
    // cout << (src >= (PI/2 - EPS)) << ' ' << (src <= (PI + EPS)) << endl;
    return src >= (PI/2 - EPS) and src <= (PI + EPS);
}

struct Query {
    Point sp, ep, center;
    double sr, er;
    
    int type;
    
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
                sr = PI / 2, er = 0;
                break;
            case 5:
                center = a.sp;
                sr = PI, er = PI/2;
                break;
        }
    }
    
    bool contain(Point src) {
        if (type >= 4) {
            // cout << (abs(center.dis(src) - r) < eps) << ' ' << isin(atan2(src.y-center.y, src.x-center.x), type) << endl;
            if (!(abs(center.dis(src) - r) < EPS and isin(atan2(src.y-center.y, src.x-center.x), type))) {
                return false;
            } else {
                sr = atan2(src.y-center.y, src.x-center.x);
                if (sr < 0) sr += 2 * PI;
                sp = src;
            }
        } else {
            if (Line(sp, ep).dis(src) > EPS) {
                // cout << Line(sp, ep).dis(src);
                return false;
            } else {
                sp = src;
            }
        }
        
        // cout << "true";
        return true;
    }
};

ostream& operator<<(ostream& stream, const Point src) {
    stream << "(" << src.x << ", " << src.y << ")";
    
    return stream;
}

ostream& operator<<(ostream& stream, const Line line) {
    stream << line.sp << ' ' << line.ep;
    
    return stream;
}

ostream& operator<<(ostream& stream, const Query src) {
    
    stream << '[' << src.type << "] ";
    
    if (src.type >= 4) {
        stream << src.center.x << ' ' << src.center.y << ' ' << src.sr << ' ' << src.er;
    } else {
        stream << src.sp.x << ' ' << src.sp.y << ", " << src.ep.x << ' ' << src.ep.y;
    }
    
    return stream;
}

bool lteps(Point a, Point b) {
    return a.dis(b) < eps;
}

vec<Query> que;
vec<Line> line;

double _ans = 0;

bool examine(int idx) {
    if (que[idx].type >= 4) {   //* rotate.
        double L = que[idx].sr, R = que[idx].er, ans = L;
        
        int count = 0;
        while (L-R > eps and count++ <= 1000) {
            double nM = (L+R) / 2;
            Point M = Point(que[idx].center.x + r * cos(nM), que[idx].center.y + r * sin(nM));
            
            bool _good = true;
            for (auto i : line) {
                if (r - i.dis(M) > eps)
                    _good = false;
            }
            
            if (_good) {
                L = nM;
                ans = nM;
            } else {
                R = nM;
            }
        }
        
        que[idx].er = ans;
        que[idx].ep = Point(que[idx].center.x + r * cos(ans), que[idx].center.y + r * sin(ans));
        _ans += r * (que[idx].sr - que[idx].er);
    } else {
        Point L = que[idx].sp, R = que[idx].ep, ans = L;
        // cout << L << ' ' << R << endl;
        int count = 0;
        while (!lteps(L, R) and count++ <= 1000) {
            Point M = (L+R) / 2;
            
            // cout << M << endl;
            
            bool _good = true;
            for (auto i : line) {
                if (r - i.dis(M) > eps) {
                    // cout << "collision with " << i << endl;
                    _good = false;
                    break;
                }
            }
            
            if (_good) {
                L = M;
                ans = M;
            } else {
                R = M;
            }
        }
        
        que[idx].ep = ans;
        _ans += que[idx].ep.dis(que[idx].sp);
    }
    
    // cout << idx << '/' << que.size()-1 << endl;
    // cout << "-> " << que[idx].type << ' ' << que[idx].sp << que[idx].ep << endl << flush;
    
    /*
    if (idx != que.size() - 1) {
        for (int i = idx+1; ; i++) {
            if (idx == que.size())
                return true;
                
            if (que[i].contain(que[idx].ep)) {
                nxt = i;
                break;
            }
       }
    }
    */
    cout << '[';
    for (int i = 0; i < que.size(); i++) {
            // cout << i << ": ";
            if (que[i].contain(que[idx].ep)) {
                nxt = i;
            }
            // cout << endl;
        cout << que[i].contain(que[idx].ep);
    }
    cout << "]\n";
    
    return (idx != que.size() - 1);
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> r >> n) {
        if (n == 0) break;
        
        _ans = 0;
        
        vec<pdd> _list(n);
        for (auto &i : _list)
            cin >> i.F >> i.S;
        
        double nx = 0, ny = 0;
        
        line.clear();
        for (int i = 0; i < n; i++) {
            line.eb(Line(Point(nx, ny), Point(nx + _list[i].F, ny)));
            nx += _list[i].F;
            
            
            if (i != n-1)
                line.eb(Line(Point(nx, ny), Point(nx, ny + _list[i].S)));
            ny += _list[i].S;
        }
        
        que.clear();
        for (int i = 0; i < line.size(); i++) {
            if (i % 2) {    //* vertical.
                if (line[i].sp.y > line[i].ep.y) {
                    que.eb(2, line[i]);
                } else {
                    que.eb(3, line[i]);
                    que.eb(5, line[i+1]);
                }
            } else { //* horizontal
                que.eb(Query(1, line[i]));
                
                if (i != n-1 and line[i+1].sp.y > line[i+1].ep.y)
                    que.eb(Query(4, line[i]));
            }
        }
        
        // for (auto i : que)
        //     cout << i << endl;
        
        nxt = 0;
        while(examine(nxt));
        
        cout << "Case " << c++ << ": Distance = " << fixed << setprecision(3) << _ans << endl << endl;
        
        cout << flush;
    }
}