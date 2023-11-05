#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll mPOW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll nPOW(ll a, ll b) { ll res=1; do { if(b%2) res*=a; a*=a; } while (b>>=1); return res; }
ll mFAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
ll nFAC(ll a) { ll res = 1; REP1(i, a) res*=i; return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

class Point {
    public:
        double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    double operator^(Point src) {
        return x * src.y - y * src.x;
    }
    
    bool operator==(Point src) {
        return (x == src.x and y == src.y);
    }
    
    bool operator<(Point src) {
        if (x != src.x)
            return x < src.x;
        return y < src.y;
    }
};

ostream& operator<<(ostream& os, Point src) {
    os << "(" << src.x << ", " << src.y << ")";
    
    return os;
}

class Line {
    public:
        Point sp, ep;
        
    Line() {}
    Line(Point s, Point e) : sp(s), ep(e) {}
    
    double ori(Point src) {
        return (ep-sp) ^ (src-sp);
    }
};

double ansmin, ansmax;

inline int next(int b, int r) {
    return (b+1) % r;
}

Point rotate(Point src, double rad) {
    double x = src.x * cos(rad) - src.y * sin(rad);
    double y = src.x * sin(rad) + src.y * cos(rad);
    
    return Point(x, y);
}

double cal(vec<Point> hull, double rad) {
    for (int i = 0; i < hull.size(); i++) {
        hull[i] = rotate(hull[i], -rad);
    }
    
    double left = INF, right = nINF, up = nINF, down = INF;
    for (int i = 0; i < hull.size(); i++) {
        left = min(left, hull[i].x);
        right = max(right, hull[i].x);
        up = max(up, hull[i].y);
        down = min(down, hull[i].y);
    }
    
    return (up-down) * (right-left);
}

void print(vec<Point> hull, double rad) {
    devec(hull);
    debug(rad);
    for (int i = 0; i < hull.size(); i++) {
        hull[i] = rotate(hull[i], -rad);
    }
    
    devec(hull);
}

double eps = 1e-10;
double PI = 3.1415926535;
void tri_search(vec<Point> hull, int idx) {
    int _s = hull.size();
    
    //* slope
    Point f = hull[next(idx, _s)] - hull[idx], s = hull[next(idx+1, _s)] - hull[next(idx, _s)];
    
    //* find min.
    double L = atan(f.y / f.x), R = atan(s.y / s.x);
    if (idx == hull.size()-1)
        R += 2 * PI;
    
    while (R-L >= eps) {
        double Lmid = L + (R-L) / 3, Rmid = R - (R-L) / 3;
        
        if (cal(hull, Lmid) < cal(hull, Rmid))
            R = Rmid;
        else 
            L = Lmid;
    }
    
    ansmin = min(ansmin, cal(hull, L));
    // print(hull, L);
    
    //* find max.
    L = atan(f.y / f.x), R = atan(s.y / s.x);
    if (idx == hull.size()-1)
        R += 2 * PI;
        
    while (R-L >= eps) {
        double Lmid = L + (R-L) / 3, Rmid = R - (R-L) / 3;
        
        if (cal(hull, Lmid) < cal(hull, Rmid))
            L = Lmid;
        else 
            R = Rmid;
    }
    
    ansmax = max(ansmax, cal(hull, L));
    // print(hull, L);
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (n == 0) break;
        
        // if (c != 1)
            // cout << endl;
        
        vec<Point> _list(n);
        for (auto &i : _list) {
            cin >> i.x >> i.y;
        }
        
        sort(al(_list));
        
        vec<Point> hull;
        hull.reserve(_list.size()+1);
        
        for (int i = 0; i < 2; i++) {
            auto start = hull.size();
            
            for (int k = 0; k < _list.size(); k++) {
                while (hull.size() >= start + 2 and Line(hull[hull.size()-2], hull.back()).ori(_list[k]) <= 0)
                    hull.pop_back();
                hull.eb(_list[k]);
            }
            
            hull.pop_back();
            reverse(al(_list));
        }
        
        if (hull.size() == 2 and hull[0] == hull[1])
            hull.pop_back();
        
        // devec(hull);
        
        ansmin = INF, ansmax = 0;
        for (int i = 0; i < hull.size(); i++) {
            tri_search(hull, i);
        }
        
        cout << "Gift " << c++ << endl;
        cout << "Minimum area = " << fixed << setprecision(3) << ansmin << endl;
        cout << "Maximum area = " << fixed << setprecision(3) << ansmax << endl << endl;
    }
}