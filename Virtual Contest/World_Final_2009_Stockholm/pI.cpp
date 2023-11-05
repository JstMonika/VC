#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

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
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
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

struct Window {
    int x, y, w, h;
    vec<int> s;
    
    int parent;
    vec<int> child;
    
    Window() : s(6) {
        parent = -1;
    }
};

istream& operator>>(istream& in, Window& src) {
    in >> src.x >> src.y >> src.w >> src.h;
    for (auto &i : src.s)
        in >> i;
        
    return in;
}

int dx, dy, w, h;
vec<Window> _list, tmp;
void modify(Window& src) {
    if (src.parent == -1) {
        if (dx and (src.s[0] || src.s[4] || src.s[5]) == 0) src.s[5] = 1;
        if (dy and (src.s[1] || src.s[2] || src.s[3]) == 0) src.s[2] = 1;
        
        int horizontal = (src.s[0] ? src.w : 0) + (src.s[4] ? src.x : 0) + (src.s[5] ? w - src.x - src.w : 0);
        int vertical = (src.s[1] ? src.h : 0) + (src.s[2] ? src.y : 0) + (src.s[3] ? h - src.y - src.h : 0);
        
        // cout << "x,y,h,v\n";
        // cout << dx << ' ' << dy << ' ' << horizontal << ' ' << vertical << endl;
        
        if (src.s[4])
            src.x += 1. * dx * src.x / horizontal;
        if (src.s[0])
            src.w += 1. * dx * src.w / horizontal;
        if (src.s[2])
            src.y += 1. * dy * src.y / vertical;
        if (src.s[1])
            src.h += 1. * dy * src.h / vertical;    
    } else {
        src.x += tmp[src.parent].x - _list[src.parent].x;
        src.y += tmp[src.parent].y - _list[src.parent].y;
        
        int tdx = tmp[src.parent].w - _list[src.parent].w, tdy = tmp[src.parent].h - _list[src.parent].h;
        int horizontal = (src.s[0] ? src.w : 0) + (src.s[4] ? src.x - tmp[src.parent].x : 0) + (src.s[5] ? tmp[src.parent].w - (src.x - tmp[src.parent].x) - src.w : 0);
        int vertical = (src.s[1] ? src.h : 0) + (src.s[2] ? src.y - tmp[src.parent].y : 0) + (src.s[3] ? tmp[src.parent].h - (src.y - tmp[src.parent].y) - src.h : 0);
        
        if (src.s[4])
            src.x += 1. * tdx * (src.x - tmp[src.parent].x) / horizontal;
        if (src.s[0])
            src.w += 1. * tdx * src.w / horizontal;
        if (src.s[2])
            src.y += 1. * tdy * (src.y - tmp[src.parent].y) / vertical;
        if (src.s[1])
            src.h += 1. * tdy * src.h / vertical;    
    }
}

int main()
{
    yccc;
    
    int n, k, c = 1;
    while (cin >> n >> k >> w >> h) {
        if (!n) break;
        
        _list.resize(n);
        for (auto &i : _list)
            cin >> i;
        
        for (int r = 0; r < n; r++) {
            for (int s = 0; s < n; s++) {
                if (_list[r].x < _list[s].x and _list[r].x + _list[r].w > _list[s].x + _list[s].w and
                    _list[r].y < _list[s].y and _list[r].y + _list[r].h > _list[s].y + _list[s].h) {
                    
                    if (_list[s].parent == -1)
                        _list[s].parent = r;
                    else {
                        if (_list[r].x > _list[_list[s].parent].x)
                            _list[s].parent = r;
                    }   
                }
            }
        }
        
        for (int r = 0; r < n; r++) {
            if (_list[r].parent != -1)
                _list[_list[r].parent].child.eb(r);
        }
        
        for (int i = 0; i < k; i++) {
            cin >> dx >> dy;
            
            dx -= w;
            dy -= h;
            
            tmp = _list;
            
            queue<int> que;
            for (int r = 0; r < n; r++) 
                if (_list[r].parent == -1) que.emplace(r);
            
            while (!que.empty()) {
                auto now = que.front();
                que.pop();
                
                modify(tmp[now]);
                
                for (auto r : tmp[now].child)
                    que.emplace(r);
            }
            
            cout << "Case " << c << ", resize operation " << i+1 << ":\n";
            for (int r = 0; r < n; r++)
                cout << "    Window " << r+1 << ", x = " << tmp[r].x << ", y = " << tmp[r].y << ", width = " << tmp[r].w << ", height = " << tmp[r].h << endl;
            //* print
        }
        
        c++;
    }
}