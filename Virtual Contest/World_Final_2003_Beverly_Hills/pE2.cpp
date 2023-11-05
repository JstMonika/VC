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

int dx, dy;

int next(int i, int n) {
    return (i+1) % n;
}

struct Point {
    int x, y;
    
    Point() {}
    Point(int x, int y) : x(x), y(y) {}
    
    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }
    
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

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}    
};

struct Polygon {
    vec<Point> p;
    vec<int> tx, ty;
    vec<Line> l;
    vec<vec<int>> _idx;
    vec<int> type;  //* 0 ~ 3: up, right, down, left area is inside.
    
    int clockwise;
    
    Polygon() {}
    Polygon(vec<Point> src) : p(src) {
        tx.resize(p.size());
        ty.resize(p.size());
        
        _idx.clear();
        _idx.resize(2);
        
        double area = 0;
        
        int n = src.size();
        for (int i = 0; i < n; i++) {
            l.eb(Line(p[i], p[next(i, n)]));
            area += (p[i] ^ p[next(i, n)]);
        }
        
        clockwise = area > 0 ? -1 : 1;
        
        type.resize(n);
        for (int i = 0; i < n; i++) {
            if (l[i].sp.x == l[i].ep.x) {
                type[i] = ((l[i].ep.y - l[i].sp.y) * clockwise > 0) ? 1 : 3;
                _idx[0].eb(i);
            } else {
                type[i] = ((l[i].ep.x - l[i].sp.x) * clockwise < 0) ? 0 : 2;
                _idx[1].eb(i);
            }
        }
    }
};

ostream& operator<<(ostream& out, Point src) {
    out << "[" << src.x << ", " << src.y << "]";
    
    return out;
}

int n, m;
Polygon hole, cover;

bool check() {
    return false;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n >> m) {
        if (n == 0) break;
        
        vec<Point> tmp(n);
        for (int i = 0; i < n; i++) {
            cin >> tmp[i].x >> tmp[i].y;
        }
        
        hole = Polygon(tmp);
        
        tmp.resize(m);
        for (int i = 0; i < m; i++) {
            cin >> tmp[i].x >> tmp[i].y;
        }
        
        cover = Polygon(tmp);
        
        bool good = false;
        
        // cout << hole._idx[0].size() << ' ' << hole._idx[1].size() << ' ' << cover._idx[0].size() << ' ' << cover._idx[1].size() << endl;
        for (int i = 0; i < hole._idx[0].size(); i++) {
            for (int k = 0; k < hole._idx[1].size(); k++) {
                for (int r = 0; r < cover._idx[0].size(); r++) {
                    if (cover.type[cover._idx[0][r]] != hole.type[hole._idx[0][i]]) continue;
                    
                    for (int s = 0; s < cover._idx[1].size(); s++) {
                        if (cover.type[cover._idx[1][s]] != hole.type[hole._idx[1][k]]) continue;
                        
                        dx = hole.p[i].x - cover.p[r].x, dy = hole.p[k].y - cover.p[s].y;
                        
                        if (check()) {
                            good = true;
                            goto answer;
                        }
                    }
                }
            }
        }
        
        answer:
            cout << "Hole " << c++ << ": " << (good ? "Yes\n" : "No\n");
        cout << flush;
    }
}