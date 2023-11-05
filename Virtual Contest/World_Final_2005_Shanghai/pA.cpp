#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
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

    Point() {}
    Point(double x, double y) : x(x), y(y) {}

    double operator*(Point src) {
        return x * src.x + y * src.y;
    }

    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }

    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }

    Point operator*(double src) {
        return Point(x * src, y * src);
    }

    double dis(Point src) {
        double dx = x - src.x, dy = y - src.y;

        return sqrt(dx * dx + dy * dy);
    }

    bool operator!=(Point src) {
        return (x != src.x or y != src.y);
    }

    bool operator<(Point src) {
        if (x != src.x)
            return x < src.x;
        return y < src.y;
    }
};

struct Line {
    bool dir;
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {
    }
    
    double dis(Point src) {
        double ret;

        if (dir)
            ret = src.x - sp.x;
        else
            ret = src.y - sp.y;

        return ret;
    }

    void modify() {
        dir = (sp.x == ep.x);

        if (ep < sp) {
            Point tmp = sp;
            sp = ep;
            ep = tmp;
        }
    }
};

ostream& operator<<(ostream& out, Line src) {
    
    cout << '(' << src.sp.x << ", " << src.sp.y << ") <-> (" << src.ep.x << ", " << src.ep.y << ")";

    return out;
}

double scale, offsetX, offsetY;
double mx(double src) {
    return src * scale + offsetX;
}

double my(double src) {
    return src * scale + offsetY;
}

double clamp(double src, double _min, double _max) {
    return min(max(src, _min), _max);
}

int main() {
    yccc;

    int n, m, c = 1;
    while (cin >> n >> m) {
        if (m == 0)
            break;

        // cout << n << ' ' << m << endl;

        bool good = false;

        vec<Line> puzzle(n), image(m);
        double minX = INF, minY = INF, maxX = -INF, maxY = -INF;

        for (int i = 0; i < n; i++) {
            cin >> puzzle[i].sp.x >> puzzle[i].sp.y >> puzzle[i].ep.x >> puzzle[i].ep.y;
            puzzle[i].modify();
            
            minX = min({minX, puzzle[i].sp.x, puzzle[i].ep.x});
            maxX = max({maxX, puzzle[i].sp.x, puzzle[i].ep.x});
            minY = min({minY, puzzle[i].sp.y, puzzle[i].ep.y});
            maxY = max({maxY, puzzle[i].sp.y, puzzle[i].ep.y});
        }
        for (int i = 0; i < m; i++) {
            cin >> image[i].sp.x >> image[i].sp.y >> image[i].ep.x >> image[i].ep.y;
            image[i].modify();
        }

        

        auto tmp = puzzle;
        for (int i = 0; i < 2 * n; i++) {
            for (int k = 0; k < 2 * m; k++) {
                for (int sk = 0; sk < m; sk++) {
                    if (sk / 2 == k) continue;
                    if (puzzle[(i <= 1 ? 1 : 0)].dir != image[sk].dir) continue;
                    
                    Point qi = (i%2 ? puzzle[i/2].sp : puzzle[i/2].ep);
                    Point qk = (k%2 ? image[k/2].sp : image[k/2].ep);

                    
                    scale = image[sk].dis(qk) / puzzle[(i <= 1 ? 1 : 0)].dis(qi);
                    if (scale > 1) continue;
                    if (scale <= 0) continue;

                    offsetX = qk.x - qi.x * scale;
                    offsetY = qk.y - qi.y * scale;
                    
                    vec<Line> subset;
                    for (int q = 0; q < m; q++) {
                        if (image[q].dir) {  // vertical.
                            if (image[q].sp.x < mx(minX) or image[q].sp.x > mx(maxX))
                                continue;
                            
                            if (image[q].sp.y > my(maxY) and image[q].ep.y > my(maxY))
                                continue;
                            if (image[q].sp.y < my(minY) and image[q].ep.y < my(minY))
                                continue;
                            
                            subset.eb(Line(
                                Point(image[q].sp.x, clamp(image[q].sp.y, my(minY), my(maxY))), 
                                Point(image[q].ep.x, clamp(image[q].ep.y, my(minY), my(maxY)))
                            ));
                        } else {
                            if (image[q].sp.y < my(minY) or image[q].sp.y > my(maxY))
                                continue;
                            
                            if (image[q].sp.x > mx(maxX) and image[q].ep.x > mx(maxX))
                                continue;
                            if (image[q].sp.x < mx(minX) and image[q].ep.x < mx(minX))
                                continue;
                            
                            subset.eb(Line(
                                Point(clamp(image[q].sp.x, mx(minX), mx(maxX)), image[q].sp.y), 
                                Point(clamp(image[q].ep.x, mx(minX), mx(maxX)), image[q].ep.y)
                            ));
                        }
                    }

                    auto cmp = [](Line a, Line b){
                        
                        if (a.sp != b.sp)
                            return a.sp < b.sp;
                        return a.ep < b.ep;
                    };

                    sort(al(subset), cmp);
                    sort(al(tmp), cmp);
                    

                    if (subset.size() != tmp.size())
                        continue;
                    
                    
                    bool test_good = true;
                    for (int z = 0; z < tmp.size(); z++) {
                        if (tmp[z].sp * scale + Point(offsetX, offsetY) != subset[z].sp)
                            test_good = false;
                        if (tmp[z].ep * scale + Point(offsetX, offsetY) != subset[z].ep)
                            test_good = false;
                    }

                    if (!test_good) continue;

                    // cout << "scale: " << image[sk].dis(qk) << ' ' << puzzle[(i <= 1 ? 1 : 0)].dis(qi) << endl;
                    // cout << scale << ' ' << offsetX << ' ' << offsetY << endl;
                    // cout << qi.x << ' ' << qi.y << endl;
                    // cout << qk.x << ' ' << qk.y << endl;
                    // cout << puzzle[(i <= 1 ? 1 : 0)].sp.x << ' ' << puzzle[0].sp.y << endl;
                    // cout << image[sk].sp.x << ' ' << image[sk].sp.y << endl;
                    /*
                    for (int z = 0; z < tmp.size(); z++)
                        cout << tmp[z] << endl;
                    for (int z = 0; z < subset.size(); z++)
                        cout << subset[z] << endl;
                    */  

                    good = true;
                    goto ans;
                }
            }
        }

        ans:
        cout << "Case " << c++ << ": " << (good ? "valid puzzle\n\n" : "impossible\n\n");
    }
}