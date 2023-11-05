#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
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

bool vis[20][20][20];

map<string, int> d;
int x, y, z, ans;

struct Point {
    int x, y, z;
    string dir;

    Point() {}

    Point oppo() const {
        Point src = *this;
        switch (d[dir]) {
            case 0:
                src.x--;
                src.dir = "-x";
                break;
            case 1:
                src.x++;
                src.dir = "+x";
                break;
            case 2:
                src.y--;
                src.dir = "-y";
                break;
            case 3:
                src.y++;
                src.dir = "+y";
                break;
            case 4:
                src.z--;
                src.dir = "-z";
                break;
            case 5:
                src.z++;
                src.dir = "+z";
        }

        return src;
    }

    bool operator==(Point src) {
        return x == src.x and y == src.y and z == src.z and dir == src.dir;
    }
};

Point st, ed;
vec<Point> status;

ostream& operator<<(ostream& out, Point src) {
    out << src.x << ' ' << src.y << ' ' << src.z << ' ' << src.dir;

    return out;
}

istream& operator>>(istream& in, Point& src) {
    in >> src.x >> src.y >> src.z >> src.dir;
    src.x--, src.y--, src.z--;

    return in;
}

bool check(Point src, bool strict = false) {
    if (strict) {
        if (src.x < 0 or src.x >= x)
        return false;
        if (src.y < 0 or src.y >= y) 
            return false;
        if (src.z < 0 or src.z >= z)
            return false;

        return true;
    }
    if (src.x < -1 or src.x > x)
        return false;
    if (src.y < -1 or src.y > y) 
        return false;
    if (src.z < -1 or src.z > z)
        return false;

    return true;
}

int sta = 0;
void go(int i, Point now) {
    status.eb(now);
    sta++;
    // cout << "-> " << now << ' ' << now.oppo() << endl;
    if (now.oppo() == ed) {
        ans = min(i, ans);
        // cout << "return to " << --sta << "\n";
        return;
    }

    if (i == 6) {
        // cout << "return to " << --sta << "\n";
        return;
    }

    Point tmp;
    int *px, *py, *pz;
    vec<char> nDir;
    switch (d[now.dir]) {
        case 0:
        case 1:
            px = &tmp.x;
            py = &tmp.y;
            pz = &tmp.z;
            nDir = {'x', 'y', 'z'};
            break;
        case 2:
        case 3:
            px = &tmp.y;
            py = &tmp.x;
            pz = &tmp.z;
            nDir = {'y', 'x', 'z'};
            break;
        case 4:
        case 5:
            px = &tmp.z;
            py = &tmp.x;
            pz = &tmp.y;
            nDir = {'z', 'x', 'y'};
    }
    int gx[8] = {1, 1, 1, 1, 2, 2, 2, 2};
    int gy[8] = {3, 0, -3, 0, 2, 0, -2, 0};
    int gz[8] = {0, 3, 0, -3, 0, 2, 0, -2};
    int gdir[8] = {1, 2, 1, 2, 1, 2, 1, 2};

    for (int k = 0; k < 8; k++) {
        tmp = now;
        // cout << *px << ' ' << *py << ' ' << *pz << endl;

        if (tmp.dir[0] == '+')
            *px += gx[k];
        else
            *px -= gx[k];
        
        *py += gy[k];
        *pz += gz[k];

        tmp.dir = string() + (k % 4 < 2 ? '+' : '-') + (nDir[gdir[k]]);
        
        // cout << "tmp: " << tmp << ", " << (check(tmp) ? "good" : "bad") << endl;
        
        if (check(tmp)) {
            vec<Point> que;
            bool good = true;

            tmp = now;
        
            int tx = gx[k], ty = gy[k], tz = gz[k];

            do {
                
                if (!check(tmp, true)) {
                    good = false;
                    break;
                }
                
                if (vis[tmp.x][tmp.y][tmp.z]) {
                    good = false;
                    break;
                } else {
                    vis[tmp.x][tmp.y][tmp.z] = true;
                    que.eb(tmp);
                }
                
                // cout << "good " << tmp << endl;
                *px += (tmp.dir[0] == '+' ? 1 : -1);
                tx--;
            } while (tx != 0);
            
            if (good) {
                do {
                    if (!check(tmp, true)) {
                        // cout << "first " << tmp << endl;
                        good = false;
                        break;
                    }
                    
                    // cout << tmp.x << " " << tmp.y << " " << tmp.z << endl << flush;
                    if (vis[tmp.x][tmp.y][tmp.z]) {
                        // cout << "second " << tmp << endl;
                        good = false;
                        break;
                    } else {
                        // cout << tmp << endl;
                        vis[tmp.x][tmp.y][tmp.z] = true;
                        que.eb(tmp);
                    }
                    
                    // cout << "good " << tmp << endl;

                    *py += (ty != 0 ? (ty / abs(ty)) : 0);
                    *pz += (tz != 0 ? (tz / abs(tz)) : 0);

                    ty += (ty != 0 ? (ty < 0 ? 1 : -1) : 0);
                    tz += (tz != 0 ? (tz < 0 ? 1 : -1) : 0);
                } while (ty != 0 or tz != 0); 
            } // else cout << "jump 1\n";
            

            if (good) {
                tmp.dir = string() + (k % 4 < 2 ? '+' : '-') + (nDir[gdir[k]]);
                go(i+1, tmp);
                for (auto r : que)
                    vis[r.x][r.y][r.z] = false;
            }
            else {
                // cout << "jump 2\n";
                // for (auto r : status)
                //     cout << r << ' ' ;
                // cout << tmp << endl;

                for (auto r : que) {
                    // cout << r << endl;
                    vis[r.x][r.y][r.z] = false;
                }
            }
        }
    }
    
    // cout << "return to " << --sta << "\n";
    status.erase(prev(status.rbegin().base()));
    return;
}

int main()
{
    yccc;
    d["+x"] = 0;
    d["-x"] = 1;
    d["+y"] = 2;
    d["-y"] = 3;
    d["+z"] = 4;
    d["-z"] = 5;
    
    int c = 1;
    while (cin >> x) {
        if (!x) break;
        cin >> y >> z;

        memset(vis, 0, sizeof(vis));
        ans = INF;

        cin >> st >> ed;

        ed.dir[0] = '+' + '-' - ed.dir[0];

        go(0, st);

        cout << "Case " << c++ << ": " << (ans == INF ? "Impossible" : to_string(ans)) << endl;
    }
}