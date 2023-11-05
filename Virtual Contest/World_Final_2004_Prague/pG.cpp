#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
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

struct Point {
    double x, y, d, t;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    double dis(Point src) { 
        double dx = src.x - x, dy = src.y - y;
        return sqrt(dx * dx + dy * dy);
    }
};

ostream& operator<<(ostream& out, Point src) {
    cout << src.x << ' '<< src.y;
    
    return out;
}

const double eps = 1e-9;
const double PI = acos(-1);

int calDeg(double x, double y, double dx, double dy) {
    double deg = atan2(dy - y, dx - x) / 2 / PI * 360;
    
    (deg *= -1) += 90;
    if (deg < 0) deg += 360;
    
    // cout << dy << ' ' << y <<  ' ' << dx << x << endl;
    return round(deg);
}

double clamp(double v, double m, double M) {
    return max(m, min(v, M));
}

double deg(double rad) {
    return rad / 2 / PI * 360;
}

double rad(double deg) {
    return deg * 2 * PI / 360;
}

double rotateDeg(double d) {
    (d *= -1) += 90;
    if (d < 0) d += 360;
    
    return d;
}

inline bool tri(double a, double b, double c) {
    double m = min({a, b, c}), M = max({a, b, c}), mid = a+b+c-m-M;
    
    return m + mid + eps >= M;
}

int main()
{
    yccc;
    
    int n, c = 1;
    double t, x, y;
    
    while (cin >> n >> t >> x >> y) {
        if (!(n or t or x or y)) break;
        
        vec<Point> _list(n);
        for (auto &i : _list) {
            cin >> i.x >> i.y >> i.d >> i.t;
            
            i.x += i.t * 100 * cos(rad(rotateDeg(i.d)));
            i.y += i.t * 100 * sin(rad(rotateDeg(i.d)));
        }
        
        // for (auto i : _list)
        //     cout << i << endl;
        
        cout << "Trial " << c++ << ": ";
        if (n == 1) {            
            if (abs(t - _list[0].t) < 0.001) {
                if (_list[0].dis(Point(x, y)) < 0.1) {
                    cout << "Arrived\n";
                } else 
                    cout << calDeg(_list[0].x, _list[0].y, x, y) << " degrees\n";
                //* calculate.
            } else cout << "Inconclusive\n";
        } else {
            double a = (t - _list[0].t) * 350, b = (t - _list[1].t) * 350;
            double c = _list[0].dis(_list[1]);
            
            // cout << a << ' ' << b << ' ' << c << endl;
            
            if (tri(a, b, c)) {
                double r = acos(clamp((a*a+c*c-b*b) / (2*a*c), -1., 1.)), ori_r = atan2(_list[1].y - _list[0].y, _list[1].x - _list[0].x);
                
                // cout << (a*a+c*c-b*b) / (2*a*c) << endl;
                // cout << "r -> " << deg(ori_r) << ' ' << deg(r) << endl;
                
                Point A(_list[0].x + a * cos(ori_r + r), _list[0].y + a * sin(ori_r + r));
                Point B(_list[0].x + a * cos(ori_r - r), _list[0].y + a * sin(ori_r - r));
                
                vec<Point> ans = {A};
                
                if (A.dis(B) > 0.1)
                    ans.eb(B);
                    
                // cout << "ans:\n";
                // for (auto k : ans)
                //     cout << k << endl;
                
                for (int i = 2; i < _list.size(); i++) {
                    auto center = _list[i];
                    
                    // cout << ans.size() << endl;
                    ans.erase(remove_if(al(ans), [&center, &t](Point src){
                        // cout << center << " <--> " << src << endl;
                        // cout << (abs(center.dis(src) - (t - center.t) * 350) > 0.1) << endl;
                        return abs(center.dis(src) - (t - center.t) * 350) > 0.1; 
                    }), ans.end());
                }
                
                if (ans.size() >= 2) {
                    cout << "Inconclusive\n";
                } else if (ans.size() == 0) {
                    cout << "Inconsistent\n";
                } else {
                    if (ans[0].dis(Point(x, y)) < 0.1) {
                        cout << "Arrived\n";
                    } else 
                        
                        cout << calDeg(ans[0].x, ans[0].y, x, y) << " degrees\n";
                }
            } else cout << "Inconsistent\n";
        }
    }
}