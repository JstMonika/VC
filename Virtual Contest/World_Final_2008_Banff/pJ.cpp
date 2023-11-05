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
    
    bool operator==(Point src) const {
        return x == src.x and y == src.y;
    }
    
    bool operator!=(Point src) const {
        return !(*this == src);
    }
    
    bool operator<(Point src) {
        if (x != src.x)
            return x < src.x;
        return y < src.y;
    }
    
    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    Point operator*(double src) {
        return Point(x * src, y * src);
    }
    
    double dis(Point src) {
        double dx = src.x - x, dy = src.y - y;
        
        return sqrt(dx * dx + dy * dy);
    }
};



struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    Line(double x, double h, double b, bool right) {
        if (right) {
            sp = Point(x, h);
            ep = Point(x + b / 2, 0);
        } else {
            sp = Point(x - b / 2, 0);
            ep = Point(x, h);
        }
    }
    
    bool operator<(Line src) {
        if (sp != src.sp)
            return sp < src.sp;
        
        if ((*this).scale() != src.scale())
            return (*this).scale() > src.scale();
            
        return dis() > src.dis();
    }
    
    pair<bool, Point> intersect(Line src) {
        
        if (fcmp(ori(src.sp) * ori(src.ep), 0) <= 0 and fcmp(src.ori(sp) * src.ori(ep), 0) <= 0) {
            if (fcmp((sp - src.sp) ^ (sp - src.ep), 0) == 0 and fcmp((ep - src.sp) ^ (ep - src.ep), 0) == 0)
                return {false, Point()};
            
            double t = ((src.ep - src.sp) ^ (sp - src.sp)) / ((ep - sp) ^ (src.ep - src.sp));
            
            return {true, sp + (ep - sp) * t};
        }
        
        return {false, Point()};
    }
    
    double ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
    
    
    double dis() {
        Point ret = (ep - sp);
        
        return sqrt(ret.y * ret.y + ret.x * ret.x);
    }
    
    double scale() {
    Point ret = (ep - sp);
    
    return ret.y / ret.x;
    }
};


int main()
{
    yccc;
    
    double ans;
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        ans = 0;
        
        vec<pair<Line, vec<pair<Point, int>>>> _list;
        for (int i = 0; i < n; i++) {
            double x, h, b;
            cin >> x >> h >> b;
            
            _list.eb(make_pair(Line(x, h, b, false), vec<pair<Point, int>>()));
            _list.eb(make_pair(Line(x, h, b, true), vec<pair<Point, int>>()));
        }
        
        auto cmp = [](pair<Line, vec<pair<Point, int>>> a, pair<Line, vec<pair<Point, int>>> b) {
            return a.F < b.F;
        };
        
        
        sort(al(_list), cmp);
        
        _list.eb(make_pair(Line(Point(-INF, 0), Point(INF, 0)), vec<pair<Point, int>>()));
        
        // cout << _list.size() << endl;
        
        for (int i = 0; i < _list.size(); i++) {
            for (int k = i+1; k < _list.size(); k++) {
                Point ret;
                bool good;
                tie(good, ret) = _list[i].F.intersect(_list[k].F);
                
                if (good) {
                    _list[i].S.eb(make_pair(ret, k));
                    _list[k].S.eb(make_pair(ret, i));
                }
            }
        }
        
        auto cmpVec = [&](pair<Point, int> a, pair<Point, int> b) {
            if (fcmp(a.F.x, b.F.x) != 0 or fcmp(a.F.y, b.F.y) != 0)
                return a.F < b.F;
            
            if (fcmp(_list[a.S].F.scale() - _list[b.S].F.scale(), 0) != 0)
                return _list[a.S].F.scale() > _list[b.S].F.scale();

            // cout << "dis: " << dis(_list[a.S].F) << ' ' << dis(_list[b.S].F) << endl;
            
            return _list[a.S].F.dis() > _list[b.S].F.dis();
        };
        for (int i = 0; i < _list.size(); i++) {
            
            // cout << "now: " << _list[i].F.sp.x << ' ' << _list[i].F.sp.y << endl;
            // cout << _list[i].F.ep.x << ' ' << _list[i].F.ep.y << endl;
            sort(al(_list[i].S), cmpVec);
            
            // for (auto k : _list[i].S) {
            //     cout << k.F.x << ' ' << k.F.y << ' ' << k.S << endl;
            // }
            // cout << "---\n";
        }
        
        
        
        int idx = 0;
        auto now = _list[0].S[0];
        
        // cout << now.F.x << ' ' << now.F.y << endl;
        // cout << _list.back().S.back().F.x << ' ' << _list.back().S.back().F.y << ' ';
        // cout << _list.back().S.back().S << endl;
        while (now.F != _list.back().S.back().F) {
            auto next = upper_bound(al(_list[idx].S), now, cmpVec);
            
            while (_list[(*next).S].F.scale() < _list[idx].F.scale() and (*next).F != _list[idx].F.ep) next++;
            // if (next == _list[idx].S.end()) {
            //     cout << "---\n";
            //     for (auto i : _list[idx].S) {
            //         cout << i.F.x << ' ' << i.F.y << ' ' << i.S << endl;
            //     }
                
            //     cout << "here\n";
            //     break;
            // }
            
            // cout << idx << endl;
            // cout << (*next).F.x << ' ' << (*next).F.y << ' ' << (*next).S << endl;
            // cout << "---\n";
            
            if (!(fcmp(now.F.y, 0) == 0 and fcmp((*next).F.y, 0) == 0))
                ans += now.F.dis((*next).F);
            
            now = (*next);
            swap(idx, now.S);
        }
        
        cout << "Case " << c++ << ": " << round(ans) << endl << endl;
    }
}