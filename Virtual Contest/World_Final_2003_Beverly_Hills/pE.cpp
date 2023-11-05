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

int next(int i, int n) {
    return (i+1) % n;
}

struct Point {
    int x, y;
    
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator*(Point src) {
        return x * src.x + y * src.y;
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    Point& operator+=(Point src) {
        x += src.x;
        y += src.y;
        
        return *this;
    }
    
    bool operator==(Point src) {
        return x == src.x && y == src.y;
    }
};

ostream& operator<<(ostream& out, Point src) {
    out << "[" << src.x << ", " << src.y << "]";
    
    return out;
}

int n, m, c0, c1;

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep - sp) ^ (src - sp);
    }
    
    bool test(Line line, bool clockwise, bool bigger) {
        int dx = ep.x - sp.x, dy = ep.y - sp.y;
        
        if (ori(line.sp) == 0 and ((sp - line.sp) * (ep - line.sp) < 0)) {
            if (!dx) {
                if (dy * c0 * (line.ep.x - line.sp.x) < 0) return false;
                
                if (bigger and ori(line.ep) == 0) {
                    if (min({sp.y, ep.y, line.sp.y, line.ep.y}) != min(sp.y, ep.y) or max({sp.y, ep.y, line.sp.y, line.ep.y}) != max(sp.y, ep.y)) {
                        return false;
                    }
                }
            } else {
                if (dx * c0 * (line.ep.y - line.sp.y) > 0) return false;
                
                if (bigger and ori(line.ep) == 0) {
                    if (min({sp.x, ep.x, line.sp.x, line.ep.x}) != min(sp.x, ep.x) or max({sp.x, ep.x, line.sp.x, line.ep.x}) != max(sp.x, ep.x)) {
                        return false;
                    }
                }
            }
        }
        
        if (ori(line.ep) == 0 and ((sp - line.ep) * (ep - line.ep) < 0)) {
            if ((sp - line.sp) * (ep - line.sp) > 0) return false;
            
            if (!dx) {
                if (dy * c0 * (line.sp.x - line.ep.x) < 0) return false;
            } else {
                if (dx * c0 * (line.sp.y - line.ep.y) > 0) return false;
            }
        }
        
        return true;
    }
    
    bool intersect(Line line) {
        if (!test(line, c0, false))
            return true;
        if (!line.test(*this, c1, true))
            return true;
        
        // cout << sp << ' ' << ep << " <---> " << line.sp << ' ' << line.ep << ": " << ori(line.sp) * ori(line.ep) << ", " << line.ori(sp) * line.ori(ep) << endl;
        return (ori(line.sp) * ori(line.ep) < 0 and line.ori(sp) * line.ori(ep) < 0);
    }
};

vec<vec<Point>> p(2);

const int OUTSIDE = 1;
const int INSIDE = 2;
const int BOUNDARY = 3; 

bool check() {
    for (int i = 0; i < n; i++) { //* hole
        for (int k = 0; k < m; k++) { //* cover
            if (Line(p[0][i], p[0][next(i, n)]).intersect(Line(p[1][k], p[1][next(k, m)]))) {
                // cout << "return false\n";
                return false;
            }
        }
    }
    
    for (int i = 0; i < 1; i++) {
        int wn = 0, result = -1;
    
        for (int k = 0; k < m; k++) {            
            if (p[0][i] == p[1][k]) {
                result = BOUNDARY;
                break;
            }
            
            if (p[0][i].y == p[1][k].y and p[0][i].y == p[1][next(k, m)].y) {
                if (min(p[1][k].x, p[1][next(k, m)].x) <= p[0][i].x and max(p[1][k].x, p[1][next(k, m)].x) >= p[0][i].x) {
                    result = BOUNDARY;
                    break;
                }
            } else {
                bool bottom = p[0][i].y < p[1][k].y;
                    
                if (bottom != (p[0][i].y < p[1][next(k, m)].y)) {
                    if (Line(p[1][k], p[1][next(k, m)]).ori(p[0][i]) == 0) {
                        result = BOUNDARY;
                        break;
                    }
                    
                    if (bottom == (Line(p[1][k], p[1][next(k, m)]).ori(p[0][i]) < 0)) {
                        // cout << "Point: " << p[0][i] << endl;
                        // cout << "Line: " << p[1][k] << ' ' << p[1][next(k, m)] << endl;
                        wn += bottom ? 1 : -1;
                    }
                }
            }
        }
        
        if (result == -1)
            result = (wn == 0) ? OUTSIDE : INSIDE;
        
        if (result == OUTSIDE) {
            return false;
        }
    }
    
    return true;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        p[0].clear();
        p[1].clear();
        
        for (int i = 0; i < n; i++) {
            Point tmp;
            cin >> tmp.x >> tmp.y;
            
            p[0].eb(tmp);
        }
        
        for (int i = 0; i < m; i++) {
            Point tmp;
            cin >> tmp.x >> tmp.y;
            
            p[1].eb(tmp);
        }

        c0 = c1 = -1;

        double tmp = 0;
        for (int i = 0; i < n; i++) {
            tmp += (p[0][i] ^ p[0][next(i, n)]);
        }
        if (tmp < 0) c0 = 1;
        
        tmp = 0;
        for (int i = 0; i < m; i++) {
            tmp += (p[1][i] ^ p[1][next(i, m)]);
        }
        if (tmp < 0) c1 = 1;
        
        bool good = false;
        for (int i = 0; i < n; i++) {
            if (p[0][i].y != p[0][next(i, n)].y) continue;
            
            for (int k = 0; k < n; k++) {
                if (p[0][k].x != p[0][next(k, n)].x) continue;
                
                for (int ti = 0; ti < m; ti++) {
                    if (p[1][ti].y != p[1][next(ti, m)].y) continue;
                    if ((p[1][ti].x - p[1][next(ti, m)].x) * (p[0][i].x - p[0][next(i, n)].x) * c0 * c1 < 0) continue;
                    
                    for (int tk = 0; tk < m; tk++) {
                        if (p[1][tk].x != p[1][next(tk, m)].x) continue;
                        // cout << (p[1][tk].y - p[1][next(tk, m)].y) << ' ' << (p[0][k].y - p[0][next(k, m)].y) << ' ' << c0 << ' ' << c1 << endl;
                        if ((p[1][tk].y - p[1][next(tk, m)].y) * (p[0][k].y - p[0][next(k, m)].y) * c0 * c1 < 0) continue;
                        
                        int dx = p[0][k].x - p[1][tk].x, dy = p[0][i].y - p[1][ti].y;
                        for (int q = 0; q < m; q++) {
                            p[1][q] += Point(dx, dy);
                        }
                        
                        
                        if (check()) {
                            devec2(p);
                            cout << endl;
                            
                            good = true;
                            goto ans;
                        }
                    }
                }
            }
        }
        
        ans:
            cout << "Hole " << c++ << ": " << (good ? "Yes\n" : "No\n");
    }
}