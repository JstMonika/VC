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

using Item = pair<double, double>;

const double PI = 3.1415926535;

class Point {
    public:
    
    double x, y;
    
    Point() {};
    Point(double a, double b) : x(a), y(b) {};
    
    friend Point operator+(Point, Point);
    friend Point operator-(Point, Point);
    
    friend double operator^(Point, Point);
};

ostream& operator<<(ostream& os, Point src) {
    os << src.x << ' ' << src.y << endl;
    
    return os;
}

int sgn(double src) {
    return (src > 0) - (src < 0);
}

double ori(Point a, Point b, Point c) {
    return sgn((b-a)^(c-a));
}

Point operator+(Point self, Point src) {
    return Point(self.x + src.x, self.y + src.y);
}

Point operator-(Point self, Point src) {
    return Point(self.x - src.x, self.y - src.y);
}

double operator^(Point self, Point src) {
    return self.x * src.y - self.y * src.x;
}

Point operator*(Point self, double val) {
    return Point(self.x * val, self.y * val);
}

double operator*(Point self, Point src) {
    return self.x * src.x + self.y * src.y;
}

Point pos(double distance, double radian) {
    return Point(distance * cos(radian), distance * sin(radian));
}

double rad(double c, double a, double b) {  //* calculate radian of C.
    return acos((a*a + b*b - c*c) / (2*a*b));
}

double distance(Point a, Point b) {
    return sqrt(abs(a.x-b.x) * abs(a.x-b.x) + abs(a.y-b.y) * abs(a.y-b.y));
}

double lawOfSines(double dA, double b, double dB) {
    return b * sin(dA) / sin(dB);
}

double rad(double src) {
    return src * 2 * PI / 360.0;
}

bool inCircle(vec<Point>& circle, Point src) {
    if (ori(circle[0], circle[1], src) == ori(circle[1], circle[2], src) and ori(circle[1], circle[2], src) == ori(circle[2], circle[0], src))
        return true;
    
    for (int i = 0; i < 3; i++) {
        if (ori(circle[i], circle[(i+1) % 3], src) * ori(circle[(i+1) % 3], circle[(i+2) % 3], src) == -1)
            return false;
    }
    
    return true;
}

double disToLine(Point p, Point a, Point b) {
    double t = (p-a) * (b-a) / ((b-a) * (b-a));
    
    return distance(p, a + (b-a) * t);
}

bool solve(vec<int>& edge, vec<Item>& item) {
    vec<Point> _list(3);
    
    // cout << "Items:\n" << item[0]  << endl;
    // cout << item[1] << endl;
    // cout << item[2] << endl;
    
    double a = edge[0], b = edge[1], c = edge[2];
    
    _list[0] = Point(0, 0);
    _list[1] = Point(a, 0);
    _list[2] = pos(b, rad(c, a, b));
    
    // cout << "_list:\n";
    // cout << _list[0] << _list[1] << _list[2];
    
    vec<Point> center(3);
    center[0] = _list[0] + pos(lawOfSines(rad(90), item[0].S, rad(c, a, b) / 2), rad(c, a, b) / 2);
    if (item[0].S > disToLine(center[0], _list[1], _list[2]))
        return false;
        
    center[1] = _list[1] + pos(lawOfSines(rad(90), item[1].S, rad(b, a, c) / 2), PI - rad(b, a, c) / 2);
    if (item[1].S > disToLine(center[1], _list[0], _list[2]))
        return false;
        
    center[2] = _list[2] + pos(lawOfSines(rad(90), item[2].S, rad(a, b, c) / 2), rad(c, a, b) + (rad(a, b, c) / 2) + PI);
    if (item[2].S > disToLine(center[2], _list[0], _list[1]))
        return false;
        
    // cout << "center*2:\n";
    // cout << center[0] << center[1] << center[2];
    
    for (int i = 0; i < 3; i++) {
        if (!inCircle(_list, center[i])) {
            // cout << "return " << i << " 0\n";
            return false;
        }
        
            
        if (distance(center[i], center[(i+1) % 3]) < item[i].F + item[(i+1) % 3].S) {
            // cout << distance(center[i], center[(i+1) % 3]) << ' ' << item[i].F + item[(i+1) % 3].S << endl;
            // cout << "return " << i << " 1\n";
            return false;
        }
        if (distance(center[i], center[(i+1) % 3]) < item[i].S + item[(i+1) % 3].F) {
            // cout << "return " << i << " 2\n";
            return false;
        }
    }
    
    return true;
}

int main()
{
    yccc;
    
    int c = 1;
    
    vec<int> edge(3);
    vec<Item> item(3);
    while (cin >> edge[0]) {
        if (edge[0] == 0)
            break;
        
        if (c != 1)
            cout << endl;
            
        cin >> edge[1] >> edge[2];
        
        
        for (auto &i : item) {
            cin >> i.F >> i.S;
            i.F /= 2;
            i.S /= 2;
            
            if (i.F > i.S)
                swap(i.F, i.S);
        }

        while (next_permutation(al(item)));
        
        bool good = false;
           
        do {
            if (solve(edge, item)) {
                good = true;
                
                cout << "Triangle number " << c++ << ":\n";
                cout << "All three stoppers will fit in the triangular space\n";
                
                break;
            }
        } while (next_permutation(al(item)));
        
        if (!good) {
            cout << "Triangle number " << c++ << ":\n";
            cout << "Stoppers will not fit in the triangular space\n";
        }
    }
}