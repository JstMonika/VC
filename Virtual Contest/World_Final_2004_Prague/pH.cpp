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

struct Point {
    double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    bool operator<(const Point src) {
        if (x != src.x)
            return x < src.x;
        return y < src.y;
    }
    
    double dis(Point src) {
        double dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx * dx + dy * dy);
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
    
    Point operator*(double t) {
        return Point(x * t, y * t);
    }
};

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
    
    bool hintersect(Line src) {
        if (ori(src.sp) * ori(src.ep) <= 0)
            if (src.ori(sp) * src.ori(ep) <= 0)
                return true;
                
        return false;
    }
    
    Point intersect(Line src) {
        double t = ((src.ep - src.sp) ^ (src.sp - sp)) / ((src.ep - src.sp) ^ (ep - sp));
        
        return sp + (ep - sp) * t;
    }
};

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        int ans = 0;
        
        vec<Line> _list;
        for (int i = 0; i < n; i++) {
            double a, b, c, d;
            cin >> a >> b >> c >> d;
            
            _list.eb(Line(Point(a, b), Point(c, d)));
        }
        
        for (int i = 0; i < n; i++) {   
            vec<Point> intersect = {_list[i].sp, _list[i].ep};
            for (int k = 0; k < n; k++) {
                if (i == k) continue;
                
                if (_list[i].hintersect(_list[k])) { //* intersect.
                    intersect.eb(_list[i].intersect(_list[k]));
                }
            }
            
            sort(al(intersect));
            
            // for (int k = 0; k < intersect.size(); k++) {
                // cout << intersect[k].x << ' ' << intersect[k].y << ", ";
            // }
            // cout << endl;
            
            for (int k = 0; k < intersect.size() - 1; k++) {
                double distance = intersect[k].dis(intersect[k+1]) - 50;
                
                if (k == 0) distance += 25;
                if (k == intersect.size() - 2) distance += 25;
                
                if (distance > 0)
                    ans += int(distance / 50) + 1;
            }
            // cout << endl;
        }
        
        cout << "Map " << c++ << endl;
        cout << "Trees = " << ans << endl;
    }
}