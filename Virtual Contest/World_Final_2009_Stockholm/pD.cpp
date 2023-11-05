#include <bits/stdc++.h>
using namespace std;

using ll = long long;
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
        return Point(src.x + x, src.y + y);
    }
    
    double dis(Point src) {
        double dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx * dx + dy * dy);
    }
};

ostream& operator<<(ostream& out, Point src) {
    out << src.x << ' ' << src.y << endl;
    return out;
}

double M;
vec<Point> p(4);
vec<int> o = {0, 1, 2, 3}, r(4);
vec<double> deg(4);

Point center;

bool check(int now) {
    if (now == 4) {
        return true;
    }
    
    if (now == 0) {
        p[o[now]] = Point(0, r[o[now]]);
        deg[o[now]] = PI * 3 / 2;
        
        if (check(now+1))
            return true;
    } else {
        for (int i = now-1; i >= 0; i--) {
            double a = r[o[now]] + r[o[i]], b = M - r[o[i]], c = M - r[o[now]];
            
            vec<double> test = {a, b, c};
            sort(al(test));
            if (test[0] + test[1] <= test[2]) continue;
            
            deg[o[now]] = acos((b*b + c*c - a*a) / (2 * b * c)) + deg[o[i]];
            
            p[o[now]] = center + Point(cos(deg[o[now]]) * (M-r[o[now]]), sin(deg[o[now]]) * (M-r[o[now]]));
            
            bool good = true;
            for (int k = 0; k <= now-1; k++) {
                if (fcmp(p[o[now]].dis(p[o[k]]), r[o[now]] + r[o[k]]) < 0)
                    good = false;
            }
            
            if (!good) continue;
            
            if (fcmp(p[o[now]].dis(center), M - r[o[now]]) > 0)
                continue;
            
            if (check(now+1))
                return true;
        }
    }
    
    return false;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> r[0] >> r[1] >> r[2] >> r[3]) {
        if (r[0] == 0) break;
        
        double L = 0, R = 50000;
        while (fcmp(R-L, 0)) {
            M = (L+R) / 2;
            center = Point(0, M);
            
            o = {0, 1, 2, 3};
            
            bool good;
            do {
                good = check(0);
                if (good) break;
            } while (next_permutation(al(o)));
            
            if (good) R = M;
            else L = M;
        }
        
        cout << "Case " << c++ << ": " << round(L) << endl;
    }
}