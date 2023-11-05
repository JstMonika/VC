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

    double operator^(Point src) {
        return x * src.y - y * src.x;
    }

    Point operator*(double src) {
        return Point(x * src, y * src);
    }

    double operator*(Point src) {
        return x * src.x + y * src.y;
    }

    double dis(Point src) {
        double dx = src.x - x, dy = src.y - y;

        return sqrt(dx * dx + dy * dy);
    }
};

ostream& operator<<(ostream& out, Point src) {
    cout << src.x << ' ' << src.y;
    
    return out;
}

struct Line {
    Point sp, ep;

    Line() {}
    Line(Point sp, Point ep) : sp(sp), ep(ep) {}

    bool properIntersect(Line src) {
        return fcmp((ori(src.sp) * ori(src.ep)), 0, 1e-6) < 0 and fcmp((src.ori(sp) * src.ori(ep)), 0, 1e-6) < 0;
    }

    double properIntersect(Point center, double radius) {
        return fcmp(dis(center), radius, 1e-6);
    }
    
    double ori(Point src) {
        return (ep-sp)^(src-sp);
    }

    double dis(Point src) {
        double t = ((src-sp) * (ep-sp)) / ((ep-sp) * (ep-sp));

        t = min(1., max(0., t));
        
        return src.dis(sp + (ep-sp) * t);
    }
};

double atan2(Point sp, Point ep) {
    return atan2(ep.y - sp.y, ep.x - sp.x);
}

struct Shaft {
    Point c;
    double r, prev, next, total;
    bool clockwise;

    Shaft() {}

    double dis(Shaft src, bool circle = true) {
        Line b = find_belt(src);
        
        double cir_dis = 0;
        if (prev != INF and circle) {
            double theta = atan2(c, b.sp);
            next = theta;
            
            if (clockwise)
                theta = prev - theta;
            else
                theta -= prev;
                
            if (theta < 0) theta += 2 * PI;
            if (theta >= 2 * PI) theta -= 2 * PI;

            total = r * 2 * theta;
            
            cir_dis = r * theta;
        }

        // TODO.
        return b.sp.dis(b.ep) + cir_dis;
    }

    Line find_belt(Shaft src) {
        if (clockwise == src.clockwise) {
            double theta = atan2(c, src.c);
            double t = asin(abs(r - src.r) / c.dis(src.c));

            Point mine, yours;
            if (clockwise) {
                if (r < src.r) {
                    // cout << theta << ' ' << t << endl;
                    mine = c + Point(cos(theta + t + PI/2), sin(theta + t + PI/2)) * r;
                    yours = src.c + Point(cos((PI+theta) + t - PI/2), sin((PI+theta) + t - PI/2)) * src.r;
                } else {
                    mine = c + Point(cos(theta - t + PI/2), sin(theta - t + PI/2)) * r;
                    yours = src.c + Point(cos((PI+theta) - t - PI/2), sin((PI+theta) - t - PI/2)) * src.r;
                }

                return Line(mine, yours);
            } else {
                if (r < src.r) {
                    mine = c + Point(cos(theta - t - PI/2), sin(theta - t - PI/2)) * r;
                    yours = src.c + Point(cos((PI+theta) - t + PI/2), sin((PI+theta) - t + PI/2)) * src.r;
                } else {
                    mine = c + Point(cos(theta + t - PI/2), sin(theta + t - PI/2)) * r;
                    yours = src.c + Point(cos((PI+theta) + t + PI/2), sin((PI+theta) + t + PI/2)) * src.r;
                }

                return Line(mine, yours);
            }
        } else {
            double theta = atan2(c, src.c);
            double len = c.dis(src.c) * r / (r + src.r);

            if (clockwise) {
                Point mine = c + Point(cos(theta + acos(r / len)), sin(theta + acos(r / len))) * r;
                Point yours = src.c + Point(cos((PI+theta) + acos(r / len)), sin((PI+theta) + acos(r / len))) * src.r;

                return Line(mine, yours);
            } else {
                Point mine = c + Point(cos(theta - acos(r / len)), sin(theta - acos(r / len))) * r;
                Point yours = src.c + Point(cos((PI+theta) - acos(r / len)), sin((PI+theta) - acos(r / len))) * src.r;

                return Line(mine, yours);
            }
        }
    }
};

ostream& operator<<(ostream& out, Line src) {
    cout << src.sp << " <-> " << src.ep;
    
    return out;
}


vec<Shaft> shaft;
vec<Line> belt;
deq<bool> vis;
int n, s, e;
double ans, d, now_dis;
istream& operator>>(istream& in, Shaft& src) {
    string tmp;
    cin >> src.c.x >> src.c.y >> src.r >> tmp;
    src.clockwise = (tmp == "C");

    return in;
}

bool check(int now, int i) {
    // cout << now << ' ' << i << endl;
    // cout << "in check\n";
    
    if (fcmp(shaft[now].dis(shaft[i], false), d) >= 0) {
        // cout << "fail 1\n";
        return false; 
    }
        
    // cout << "<d pass\n";
    
    Line tmp = shaft[now].find_belt(shaft[i]);
    // cout << "now: " << tmp.sp << ' ' << tmp.ep << endl;
    
    for (auto k : belt) {
        // cout << "comparing: " << tmp.sp << ' ' << tmp.ep << endl;
        // cout << k.sp << ' ' << k.ep << ' ' << tmp.properIntersect(k) << ' ' << k.properIntersect(tmp) << endl;
        
        if (tmp.properIntersect(k)) {
            // cout << "fail 2" << endl;
            return false;
        }
    }
            
    // cout << "belt intersect pass\n";
    
    double ret;
    for (int k = 0; k < n; k++) {
        if (k == now or k == i)
            continue;
        if ((ret = tmp.properIntersect(shaft[k].c, shaft[k].r)) <= 0) {
            // cout << "fail 3 with " << i << ' ' << ret << endl;
            return false;
        } else {
            
        }
    }
        
    // cout << "pass!!!!!!!!\n";
    
    return true;
}

void go(int now) {
    // devec(vis);
    
    // if (now >= 17) ;
        // devec(vis);
        
    
    if (now == e) {
        if (ans == -1 or now_dis < ans) {
            // devec(vis);
            
            // cout << belt[0].properIntersect(belt[1]) << endl;
                
            // for (auto i : belt)
            //     cout << i.sp << ", " << i.ep << ' ' << i.sp.dis(i.ep) << endl;
            ans = now_dis;
            // cout << ans << endl;
            // cout << "---\n";
            // for (auto i : shaft)
            //     cout << i.prev * 360 / 2 / PI << ' ' << i.next * 360 / 2 / PI << ' ' << i.total << endl;
            // cout << "---\n";
        }
        return;
    }

    for (int i = 0; i < n; i++) {
        // cout << i << endl;
        // cout << now << ' ' << i << ' ' << check(now, i) << endl;
        if (!vis[i] and check(now, i)) {

            vis[i] = true;
            belt.eb(shaft[now].find_belt(shaft[i]));
            shaft[i].prev = atan2(shaft[i].c, belt.back().ep);
            // cout << i << ' ' << belt.back().ep << ' ' << shaft[i].prev << endl;
            now_dis += shaft[now].dis(shaft[i]);
            go(i);
            now_dis -= shaft[now].dis(shaft[i]);
            belt.pop_back();
            vis[i] = false;

        }
    }
}

int main()
{
    yccc;

    int c = 1;
    while (cin >> n) {
        if (!n) break;

        shaft.resize(n);
        vis.resize(n);
        for (auto &i : shaft)
            cin >> i;

        cin >> s >> e >> d;

        ans = -1;
        
        // cout << shaft[8].find_belt(shaft[7]) << endl;
        // cout << shaft[7].find_belt(shaft[8]) << endl;
                
        vis[s] = true;
        shaft[s].prev = INF;
        
        // for (int i = 0; i < n; i++)
        //     for (int k = i+1 ; k < n; k++)
        //         if (check(i, k))
        //             cout << i << ' ' << k << ' ' << check(i, k) << endl;
        
        go(s);
        vis[s] = false;
        
        if (ans != -1) {
            ans = round(ans * 100) / 100;
            cout << "Case " << c++ << ": length = " << ans << endl;
        }
        else
            cout << "Case " << c++ << ": Cannot reach destination shaft" << endl;
    }
}