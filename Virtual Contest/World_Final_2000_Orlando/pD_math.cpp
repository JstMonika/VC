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

int next(int i, int n) { return (i == n-1) ? 0 : i+1; }
int prev(int i, int n) { return (i == 0) ? n-1 : i-1; }

class Point {
    public:
        double x, y;
    
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    
    
};

Point operator+(Point a, Point b) {
    return Point(a.x+b.x, a.y+b.y);
}

Point operator-(Point a, Point b) {
    return Point(a.x-b.x, a.y-b.y);
}

bool operator<(Point a, Point b) {
    return (a.x != b.x) ? (a.x < b.x) : (a.y < b.y);
}

double operator*(Point a, Point b) {
    return a.x*b.x + a.y*b.y;
}

Point operator*(double a, Point b) {
    return Point(b.x * a, b.y * a);
}

double operator^(Point a, Point b) {
    return a.x*b.y - a.y*b.x;
}

class Line {
    public:
        Point sp, ep;
    
    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}
    
    double ori(Point src) {
        return (ep-sp)^(src-sp);
    }
};

int n;
int h;
int _set[4];
double ansmax, ansmin;

vec<Point> hull;

Point equa(Point a, Point b, Point c, Point d) {
    Point ab = b-a;
    Point cd = d-c;
    
    double q = (ab.y * c.x - ab.y * a.x - ab.x * c.y + ab.x * a.y) / (ab.x * cd.y - ab.y * cd.x);
    
    return c + q * cd;
}

bool check() {
    for (int i = 0; i < 4; i++) {
        if (next(_set[i], h) == _set[next(i, 4)])
            continue;
            
        Point center = Point((hull[_set[i]].x + hull[_set[next(i, 4)]].x) / 2, (hull[_set[i]].y + hull[_set[next(i, 4)]].y) / 2);
        Point inter = equa(hull[_set[i]], hull[next(_set[i], h)], hull[_set[next(i, 4)]], hull[prev(_set[next(i, 4)], h)]);
        
        if (distance(center, inter) > distance())
    }
}

void dfs(int now) {
    if (now == 4) {
        if (check())
            cal();
        
        return;
    }
    
    if (now == 0) {
        for (int i = 0; i < h; i++) {
            _set[0] = i;
            dfs(now+1);
        }
    } else {
        for (int i = _set[now-1]+1; i != _set[0]; i = next(i, h)) {
            _set[now] = i;
            dfs(now+1);
        }
    }
}

int main()
{
    yccc;
    
    while (cin >> n) {
        if (!n)
            break;
        
        ansmax = numeric_limits<double>::min();
        ansmin = numeric_limits<double>::max();
        
        vec<Point> _list(n);
        for (int i = 0; i < n; i++) {
            cin >> _list[i].x >> _list[i].y;
        }
        
        sort(al(_list));
        
        hull.clear();
        hull.reserve(2*n+1);
        
        for (int i = 0; i < 2; i++) {
            auto start = hull.size();
            
            for (int k = 0; k < _list.size(); k++) {
                while (hull.size() > start + 2 and Line(hull[hull.size() - 2], hull.back()).ori(_list[k]) <= 0)
                    hull.pop_back();
                hull.push_back(_list[k]);
            }
            
            hull.pop_back();
            reverse(al(_list));
        }
        
        if (hull.size() == 2 and hull[0] == hull[1])
            hull.pop_back();
        
        h = hull.size();
        dfs(0);
        
        cout << "Gift " << c++ << endl;
        cout << "Minimum area = " << fixed << setprecision(3) << ansmin << endl;
        cout << "Maximum area = " << fixed << setprecision(3) << ansmax << endl << endl;
    }
}