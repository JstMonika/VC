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
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << setw(10) << setfill(' ') << k; cout << endl; }
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
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    bool operator==(Point src) {
        return (x == src.x and y == src.y);
    }
};

istream& operator>>(istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
}

ostream& operator<<(ostream& out, Point p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
}

struct Line {
    Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep-sp) ^ (src-sp);
    }
};

int n;
vec<Point> _list;
vec<double> pDis, pre;

int prev(int i) { return (i-1+n) % n; }
int next(int i) { return (i+1) % n; }

double atan2(Point s, Point e) {
    return atan2(e.y-s.y, e.x-s.x);
}

bool isin(double src, double _min, double _max) {
    return fcmp(src, _min) >= 0 and fcmp(_max, src) >= 0;
}

bool isin(Point src, Line line) {
    if (src == line.sp or src == line.ep) return false;
    return fcmp(((line.ep - src) ^ (line.sp - src)), 0) == 0 and ((line.ep - src) * (line.sp - src) < 0);
}

bool check(int i, int k) {
    
    if (_list[prev(i)] == _list[k] or _list[next(i)] == _list[k]) return true;
    
    double st = atan2(_list[i], _list[prev(i)]), ed = atan2(_list[i], _list[next(i)]);
    double src = atan2(_list[i], _list[k]);
    
    // cout << st << ' ' << src << ' ' << ed << endl;
    
    src = src - st;
    while (fcmp(src, 0) < 0) src += 2 * PI;
    while (fcmp(2 * PI, src) < 0) src -= 2 * PI;
    
    ed = ed - st;
    // cout << fcmp(ed, 0) << endl;
    while (fcmp(ed, 0) < 0) ed += 2 * PI;
    while (fcmp(2 * PI, ed) < 0) ed -= 2 * PI;
    
    // cout << i << " " << k << ' ' << src << ' ' << ed << endl;
    
    return fcmp(src, 0) >= 0 and fcmp(src, ed) <= 0;
}

bool intersect(Line a, Line b) {
    return fcmp(a.ori(b.sp) * a.ori(b.ep), 0) < 0 and fcmp(b.ori(a.sp) * b.ori(a.ep), 0) < 0;
}

double dis(Point a, Point b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    
    return sqrt(dx*dx + dy*dy);
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n) {
        if (!n) break;
        
        _list.resize(n);
        pDis.resize(n);
        pre.resize(n);
        
        for (auto &i : _list)
            cin >> i;
        
        for (int i = 0; i < n; i++) {
            pDis[i] = dis(_list[i], _list[next(i)]);
            
            if (i) pre[i] = pre[i-1] + pDis[i];
            else pre[i] = pDis[i];
        }
        
        devec(pDis);
        devec(pre);
        
        Point pos;
        cin >> pos;
        
        int ls, ps;
        cin >> ls >> ps;
        
        vec<vec<double>> G(n+1, vec<double>(n+1, INF));
        
        for (int i = 0; i < n; i++) {
            for (int k = i+1; k < n; k++) {
                if (check(i, k)) {
                    bool good = true;
                    for (int z = 0; z < n; z++) {
                        //* can not on line i, k.
                        if (isin(_list[z], Line(_list[i], _list[k]))) {
                            good = false;
                            // cout << i << ' ' << k << ' ' << z << " fail 2\n";
                            break;
                        }
                        
                        
                        //* can not intersect z, z+1, i, k.
                        if (intersect(Line(_list[z], _list[next(z)]), Line(_list[i], _list[k]))) {
                            good = false;
                            // cout << i << ' ' << k << ' ' << z << " fail 3\n";
                            break;
                        }
                    }
                    
                    if (good) {
                        // cout << _list[i] << ' ' << _list[k] << endl;
                        // cout << i << ' ' << k << ' ' << dis(_list[i], _list[k]) << endl;
                        //TODO.
                        G[i][k] = G[k][i] = dis(_list[i], _list[k]);
                        //* build line.
                    }
                } 
                // else cout << i << ' ' << k << " fail 1\n";
            }
            
            bool good = true;
            
            for (int z = 0; z < n; z++) {
                if (isin(_list[z], Line(_list[i], pos))) {
                    good = false;
                    // cout << i << ' ' << k << ' ' << z << " fail 2\n";
                    break;
                }
                
                if (intersect(Line(_list[z], _list[next(z)]), Line(_list[i], pos))) {
                    good = false;
                    // cout << i << ' ' << k << ' ' << z << " fail 3\n";
                    break;
                }
            }
            
            if (good) {
                // cout << i << ' ' << k << endl;
                //TODO.
                G[i][n] = G[n][i] = dis(_list[i], pos);
                //* build line.
            }
        }
        
        devec2(G);
        
        for (int z = 0; z <= n; z++)
            for (int i = 0; i <= n; i++)
                for (int k = 0; k <= n; k++)
                    G[i][k] = min(G[i][k], G[i][z] + G[z][k]);
        
        devec2(G);
        
        double L = 0, R = 1e8;
        while (fcmp(R, L) > 0) {
            double M = (L + R) / 2;
            double lugDis = M * ls;
            
            // cout << M << ' ' << lugDis << endl;
            lugDis -= ll(lugDis / pre[n-1]) * pre[n-1];
            
            int idx = upper_bound(al(pre), lugDis) - pre.begin();
            
            
            double goLuggage = INF;
            Point luggage;
            
            double t = atan2(_list[idx], _list[next(idx)]);
            luggage = _list[next(idx)] - Point(cos(t), sin(t)) * (pre[idx] - lugDis);
            // cout << luggage << endl;
            
            
            for (int i = 0; i < n; i++) {   
                bool good = true;
                for (int z = 0; z < n; z++) {
                    //* can not on line i, k.
                    if (isin(_list[z], Line(_list[i], luggage))) {
                        good = false;
                        // cout << i << ' ' << z << " fail 2\n";
                        break;
                    }
                    
                    //* can not intersect z, z+1, i, k.
                    if (intersect(Line(_list[z], _list[next(z)]), Line(_list[i], luggage))) {
                        if (!(isin(_list[i], Line(_list[z], _list[next(z)])) or isin(luggage, Line(_list[z], _list[next(z)])))) {
                            
                            good = false;
                            break;
                            // cout << _list[z] << ' ' << _list[next(z)] << ' ' << _list[i] << ' ' << luggage << endl;
                            // cout << i << ' ' << z << " fail 3\n";
                        }
                    }
                    
                    if (Line(_list[idx], _list[next(idx)]).ori(_list[i]) > 0) {
                        // cout << i << ' ' << z << " fail 4\n";
                        good = false;
                        break;
                    }
                }
                
                if (good) {
                    //TODO.
                    if (goLuggage > G[n][i] + dis(_list[i], luggage)) {    
                        goLuggage = min(goLuggage, G[n][i] + dis(_list[i], luggage));
                        // cout << "->" << i << endl;
                    }
                }
            }
            
            bool good = true;
            for (int z = 0; z < n; z++) {
                //* can not on line i, k.
                if (isin(_list[z], Line(pos, luggage))) {
                    // cout << ' ' << z << " fail 1\n";
                    good = false;
                    // cout << i << ' ' << k << ' ' << z << " fail 2\n";
                    break;
                }
                
                //* can not intersect z, z+1, i, k.
                if (intersect(Line(_list[z], _list[next(z)]), Line(pos, luggage))) {
                    // cout << ' ' << z << " fail 2\n";
                    good = false;
                    break;
                }
                
                if (fcmp(Line(_list[idx], _list[next(idx)]).ori(pos), 0) > 0) {
                    // cout << ' ' << z << " fail 3\n";
                    good = false;
                    break;
                }
            }
            
            if (good) {   
                // cout << "->> " << endl;
                goLuggage = min(goLuggage, dis(pos, luggage));
            }
            
            // cout << luggage << endl;
            // cout << "Luggage: " << lugDis << ' ' << M << endl;
            // cout << "Passenger: " << goLuggage << ' ' << M << endl;
            
            goLuggage /= ps;
            
            if (goLuggage > M)
                L = M;
            else
                R = M;
        }
        
        // cout << R << endl;
        int m = int(R), s = round((R - int(R)) * 60);
        if (s == 60) s = 0, m++;
        
        cout << "Case " << c++ << ": Time = " << m << ":" << setw(2) << setfill('0') << s << endl;
    }
}