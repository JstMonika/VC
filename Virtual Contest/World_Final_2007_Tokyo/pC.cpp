#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifndef dbg
#define endl '\n'
#endif

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Point {
    double x, y;
    
    Point() { x = 0, y = 0; }
    Point(double x, double y) : x(x), y(y) {}
};

ostream& operator<<(ostream& out, Point s) {
    out << s.x << ' ' << s.y << endl;
    return out;
}

double atan2(Point src) {
    return atan2(src.y, src.x);
}

void clamp(double& src) {
    while (src >= 2 * PI)
        src -= 2 * PI;
    
    while (src < 0)
        src += 2 * PI;
}

double convert(double rad) {
    rad = rad * 360 / (2 * PI);
    
    return rad;
}


int main()
{
    yccc;
    
    int n, theta, c = 1;
    while (cin >> n >> theta) {
        if (n == 0) break;
        
        vec<Point> in(n+1), src(n+1);
        for (int i = 1; i <= n; i++) {
            cin >> in[i].x >> in[i].y;
            src[i].x = in[i].x - in[i-1].x;
            src[i].y = in[i].y - in[i-1].y;
        }
        
        // devec(src);
        
        if (all_of(al(src), [](Point s){ return s.x >= 0; }) or theta == 0)
            cout << "Case " << c++ << ": Acceptable as proposed" << endl << endl;
        else {
            vec<Point> deg(n);
            for (int i = 0; i < n; i++) {
                deg[i].x = -PI/2-atan2(src[i+1]);
                deg[i].y = PI/2-atan2(src[i+1]);
                
                clamp(deg[i].x);
                clamp(deg[i].y);
            }
            
            // devec(deg);
            
            bool good = true;
            for (int i = 0; i < n-1; i++) {
                if (deg[i].x > deg[i].y and deg[i+1].x > deg[i+1].y) {
                    deg[i+1].x = max(deg[i].x, deg[i+1].x);
                    deg[i+1].y = min(deg[i].y, deg[i+1].y);
                } else if (deg[i].x > deg[i].y or deg[i+1].x > deg[i+1].y) {
                    if (deg[i].x > deg[i].y) {
                        swap(deg[i].x, deg[i+1].x);
                        swap(deg[i].y, deg[i+1].y);
                    }
                    
                    double st = -1, ed = -1;
                    if (fcmp(deg[i+1].y, deg[i].x) > 0) {
                        st = deg[i].x;
                        ed = min(deg[i].y, deg[i+1].y);
                    }
                    
                    if (fcmp(deg[i].y, deg[i+1].x) > 0) {
                        st = max(deg[i].x, deg[i+1].x);
                        ed = deg[i].y;
                    }
                    
                    if (fcmp(deg[i+1].y, deg[i].x) == 0 and fcmp(deg[i].y, deg[i+1].x) == 0) {
                        st = ed = deg[i].y;
                    }
                    
                    if (st == -1) {
                        good = false;
                        break;
                    } else {
                        deg[i+1].x = st;
                        deg[i+1].y = ed;
                    }
                } else {
                    deg[i+1].x = max(deg[i].x, deg[i+1].x);
                    deg[i+1].y = min(deg[i].y, deg[i+1].y);
                    
                    if (deg[i+1].x > deg[i+1].y) {
                        good = false;
                        break;
                    }
                }
            }
            
            // cout << deg[n-1].x << ' ' << deg[n-1].y << endl;
            
            double degEd = -convert(deg[n-1].x), degSt = 360-convert(deg[n-1].y);
            
            if (good)
                cout << "Case " << c++ << ": Acceptable after " << (abs(degEd) > degSt ? "clockwise" : "counterclockwise") << " rotation of " <<  fixed << setprecision(2) << min(abs(degEd), degSt) << " degrees" << endl << endl;
            else
                cout << "Case " << c++ << ": Unacceptable" << endl << endl;
        }
    }
}