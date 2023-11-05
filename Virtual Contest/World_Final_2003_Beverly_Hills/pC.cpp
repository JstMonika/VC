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

double eps = 1e-9;

long long power(int a, int n) {
    long long ret = 1;
    REP(i, n) ret *= a;
    
    return ret;
}

struct Point {
    int x, y;
    double dx, dy, dis;
    
    Point() {}
    Point(double dx, double dy) : dx(dx), dy(dy) {
        x = dx;
        y = dy;
    }
    
    
    void init(int n) {
        dx *= power(3, n) - 1;
        dy *= power(3, n) - 1;
        
        x = dx;
        y = dy;
    }
    
    void find(Point& src) {
        double tmp;
        
        src.x = src.dx = (modf(dx, &tmp) <= 0.5 + eps) ? floor(dx) : ceil(dx);
        src.y = src.dy = (modf(dy, &tmp) <= 0.5 + eps) ? floor(dy) : ceil(dy);
        
        double gx = src.dx - dx, gy = src.dy - dy;
        dis = sqrt(gx * gx + gy * gy);
    }
};

ostream& operator<<(ostream& out, Point src) {
    cout << src.dx << ' ' << src.dy << endl;
    
    return out;
}

#define print(v) cout << " > " << #v << ": " << v.x << ' ' << v.y << endl;

const int times[3][3] = {
    {8, 3, 2},
    {7, 4, 1},
    {6, 5, 0},
};

const int types[3][3] = {
    {0, 2, 0},
    {1, 3, 1},
    {0, 2, 0},
};

const int typez[3][3] = {
    {1, 3, 1},
    {0, 2, 0},
    {1, 3, 1},
};

long long recur(int n, Point rs, Point re, int type, Point s) {
    if (n == 0) {
        // cout << "ends here\n";
        return 0;
    }
    
    int unit_len = power(9, n-1) - 1;
    int unit = (re.x - rs.x + 1) / 9;
    
    int x = (s.x - rs.x) / ((re.x - rs.x + 1) / 3);
    int y = (s.y - rs.y) / ((re.y - rs.y + 1) / 3);
    
    // print(rs);
    // print(re);
    // print(s);
    // cout << x << " " << y << endl;

    // cout << "type: " << type << endl;
    // cout << "rc: " << r << ' ' << c << endl;
    
    Point ns(rs.x + unit * 3 * x, rs.y + unit * 3 * y);
    Point ne(rs.x + unit * 3 * (x+1) - 1, rs.y + unit * 3 * (y+1) - 1);
    
    switch (type) {
        case 0: //* S left start
            // cout << "0-> " << times[x][y] << ' ' << (unit_len + 1) << endl;
            return recur(n-1, ns, ne, types[x][y], s) + times[x][y] * (unit_len + 1);
        case 1: //* Z left start
            // cout << "1-> " << times[x][2-y] << ' ' << (unit_len + 1) << endl;
            return recur(n-1, ns, ne, typez[x][y], s) + times[x][2-y] * (unit_len + 1);
        case 2: //* Z right start
            // cout << "2-> " << (8 - times[x][2-y]) << ' ' << (unit_len + 1) << endl;
            return recur(n-1, ns, ne, 3-typez[x][y], s) + (8 - times[x][2-y]) * (unit_len + 1);
        case 3: //* S right start
            // cout << "3-> " << (8 - times[x][y]) << ' ' << (unit_len + 1) << endl;
            return recur(n-1, ns, ne, 3-types[x][y], s) + (8 - times[x][y]) * (unit_len + 1);
    }
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        if (c != 1) cout << endl;
        
        Point sp, ep;
        cin >> sp.dx >> sp.dy >> ep.dx >> ep.dy;
        
        sp.init(n);
        ep.init(n);
        
        // print(sp);
        // print(ep);
        
        Point csp, cep;
        
        sp.find(csp);
        ep.find(cep);
        
        // print(csp);
        // print(cep);
        
        // cout << sp << ep << csp << cep;
        
        // recur(n, Point(0, 0), Point(power(3, n) - 1, power(3, n) - 1), 0, csp);
        double ans = recur(n, Point(0, 0), Point(power(3, n) - 1, power(3, n) - 1), 0, csp) - recur(n, Point(0, 0), Point(power(3, n) - 1, power(3, n) - 1), 0, cep);
        
        cout << "Case " << c++ << ".  Distance is "
             << fixed << setprecision(4) << (abs(ans) + sp.dis + ep.dis) / (power(3, n) - 1) << endl;
    }
}