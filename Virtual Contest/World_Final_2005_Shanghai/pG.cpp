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
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) {cout << ' '; if (k == INF) cout << '-'; else cout << k;} cout << endl; }

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
    int x, y;

    Point() {}
    Point(int x, int y) : x(x), y(y) {}

    Point operator+(Point src) {
        return Point(x + src.x, y + src.y);
    }
    
    Point operator-(Point src) {
        return Point(x - src.x, y - src.y);
    }
    
    bool operator==(Point src) {
        return x == src.x and y == src.y;
    }
    
    bool operator!=(Point src) {
        return !(*this == src);
    }
    
    Point operator*(int i) {
        return Point(x * i, y * i);
    }
};

ostream& operator<<(ostream& out, Point src) {
    out << "(" << src.x << ", " << src.y << ")";

    return out;
}

int next(int i, int m) {
    return (i + 1) % m;
}

int prev(int i, int m) {
    return (i + (m-1)) % m;
}


vec<pair<char, int>> ori;
vec<Point> _list;
vec<int> pre;
int n, total = 0;

Point opponent(int i) {
    Point now = _list[i];

    int idx = i, last = total / 2;
    while (ori[idx].S < last) {
        last -= ori[idx].S;

        idx = next(idx, n);
        now = _list[idx];
    }

    switch (ori[idx].F) {
        case 'N':
            return now + Point(0, last);
        case 'E':
            return now + Point(last, 0);
        case 'W':
            return now + Point(-last, 0);
        case 'S':
            return now + Point(0, -last);
    }
}

bool middle(Point src, Point f, Point s) {
    if (src.x == f.x and src.x == s.x)
        if ((src.y - f.y) * (src.y - s.y) < 0)
            return true;
    
    if (src.y == f.y and src.y == s.y)
        if ((src.x - f.x) * (src.x - s.x) < 0)
            return true;
    
    return false;
}

bool check(vec<Point> src) {
    vec<Point> tmp = {_list[0]};
    vec<int> idx(6);
    for (int i = 1; i < _list.size(); i++) {
        for (int k = 0; k < 6; k++) {
            if (middle(src[k], _list[i-1], _list[i])) {
                tmp.eb(src[k]);
                idx[k] = tmp.size()-1;
            } else if(src[k] == _list[i-1])
                idx[k] = tmp.size()-1;
        }
        
        tmp.eb(_list[i]);
    }
    
    
    for (int k = 0; k < 6; k++) {
            if (middle(src[k], _list.back(), _list[0])) {
                tmp.eb(src[k]);
                idx[k] = tmp.size()-1;
            } else if (src[k] == _list.back())
                idx[k] = tmp.size()-1;
    }
    
    // devec(tmp);
    // devec(idx);
    
    for (int i = 0; i < 3; i++) {
        int di = idx[i], dk = idx[3+i];
        Point pi = tmp[di], pk = tmp[dk];
        
        // cout << "------------\n";
        // cout << tmp[di] << " and " << tmp[dk] << endl << endl;
        
        vec<Point> first, second;
        while (pi != tmp[idx[i+1]]) {
            first.eb(tmp[next(di, tmp.size())] - tmp[di]);
            second.eb((tmp[next(dk, tmp.size())] - tmp[dk]));
            
            di = next(di, tmp.size());
            dk = next(dk, tmp.size());
            
            pi = tmp[di];
            pk = tmp[dk];
        }
        
        for (int k = 0; k < first.size(); k++) {
            // cout << first[k] << " <<<<<>>>>> " << second[first.size()-1-k] << endl;
            if (first[k] != second[first.size()-1-k] * -1)
                return false;
        }
    }
    
    // cout << "gooooooooooooooooooooooood\n";
    return true;
}

int main() {
    yccc;

    int l, c = 1;
    char ch;
    while (cin >> n) {
        if (n == 0)
            break;
        
        if (n == 4) {
            cout << "Polygon " << c++ << ": Possible\n";
            continue;
        }

        _list.clear();
        ori.resize(n);
        pre.resize(n+1);
        total = 0;

        int nowX = 0, nowY = 0;
        _list.eb(0, 0);
        for (int i = 0; i < n; i++) {
            cin >> ori[i].F >> ori[i].S;

            total += ori[i].S;
            pre[i+1] = ori[i].S + pre[i];

            switch (ori[i].F) {
                case 'N':
                    nowY += ori[i].S;
                    break;
                case 'W':
                    nowX -= ori[i].S;
                    break;
                case 'E':
                    nowX += ori[i].S;
                    break;
                case 'S':
                    nowY -= ori[i].S;
            }
            
            if (i != n-1)
                _list.eb(nowX, nowY);
        }
        
        bool good = false;
        // devec(pre);
        for (int i = 0; i < n; i++)
            for (int k = i+1; k < n; k++)
                for (int j = k+1; j < n; j++) {
                    vec<Point> que;
                    
                    if (pre[k+1] - pre[i] > total / 2) { //* k, j, i, oppo(k) ....
                        que.eb(_list[k]);
                        que.eb(_list[j]);
                        que.eb(_list[i]);
                        que.eb(opponent(k));
                        que.eb(opponent(j));
                        que.eb(opponent(i));
                    } else if (pre[j+1] - pre[i] > total / 2) { //* j, i, k, oppo(j) ....
                        que.eb(_list[j]);
                        que.eb(_list[i]);
                        que.eb(_list[k]);
                        que.eb(opponent(j));
                        que.eb(opponent(i));
                        que.eb(opponent(k));
                    } else { //* i, k, j, oppo(i) ....
                        que.eb(_list[i]);
                        que.eb(_list[k]);
                        que.eb(_list[j]);
                        que.eb(opponent(i));
                        que.eb(opponent(k));
                        que.eb(opponent(j));
                    }
                    
                    if (check(que)) {
                        good = true;
                        goto ans;
                    }
                }
        
        ans:
        cout << "Polygon " << c++ << ": " << (good ? "Possible\n" : "Impossible\n");
    }
}