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

vec<vec<vec<ll>>> _list(200, vec<vec<ll>>(200, vec<ll>(4)));
vec<vec<ll>> edge;
bool vis[200][200][4][2];

struct Status {
    int r, c;
    int dir;
    bool rotate;
    ll val;
    
    Status() {}
    Status(int r, int c, int dir, bool rotate, ll val) : r(r), c(c), dir(dir), rotate(rotate), val(val) {}
    
    bool operator<(Status src) const {
        return val > src.val;
    }
};

int r, c;

vec<Status> find_next(Status s) {
    
    vec<Status> ret;
    int value;
        
    if ((s.dir == 0 and !s.rotate) or (s.dir != 0 and s.rotate)) {
        if (s.r+1 < r) {
            value = edge[s.r * 2 + 1][s.c];
            if (value != 0) {    
                ret.eb(s.r+1, s.c, 0, true, + s.val + value * 2);
                ret.eb(s.r+1, s.c, 0, false, + s.val + value * (1 + s.rotate));
            }
        }
    }
    if ((s.dir == 2 and !s.rotate) or (s.dir != 2 and s.rotate)) {
        if (s.r-1 >= 0) {
            value = edge[s.r * 2 - 1][s.c];
            if (value != 0) {    
                ret.eb(s.r-1, s.c, 2, true, + s.val + value * 2);
                ret.eb(s.r-1, s.c, 2, false, + s.val + value * (1 + s.rotate));
            }
        }
    }
    if ((s.dir == 1 and !s.rotate) or (s.dir != 1 and s.rotate)) {
        if (s.c+1 < c) {
            value = edge[s.r * 2][s.c];
            if (value != 0) {    
                ret.eb(s.r, s.c+1, 1, true, + s.val + value * 2);
                ret.eb(s.r, s.c+1, 1, false, + s.val + value * (1 + s.rotate));
            }
        }
    }
    if ((s.dir == 3 and !s.rotate) or (s.dir != 3 and s.rotate)) {
        if (s.c-1 >= 0) {
            value = edge[s.r * 2][s.c - 1];
            if (value != 0) {    
                ret.eb(s.r, s.c-1, 3, true, + s.val + value * 2);
                ret.eb(s.r, s.c-1, 3, false, + s.val + value * (1 + s.rotate));
            }
        }
    }
    
    return ret;
}

int main()
{
    yccc;
    
    int C = 1;
    while (cin >> r >> c) {
        if (r == 0) break;
    
        memset(vis, 0, sizeof(vis));
        
        int sr, sc, tr, tc;
        cin >> sr >> sc >> tr >> tc;
        sr--, sc--, tr--, tc--;
        
        for (int i = 0; i < 200; i++)
            for (int k = 0; k < 200; k++)
                for (int j = 0; j < 4; j++)
                    _list[i][k][j] = INF;
        
        edge.resize(2*r - 1);
        fill(al(edge), vec<ll>());
        
        for (int i = 0; i < 2*r - 1; i++) {
            int idx = c - (i % 2 == 0);
            
            for (int k = 0; k < idx; k++) {
                ll tmp;
                cin >> tmp;
                
                edge[i].eb(tmp);
            }
        }
        
        priority_queue<Status> pq;
        pq.emplace(sr, sc, 0, true, 0);
        pq.emplace(sr, sc, 2, true, 0);
        
        int count = 2;
        ll ans = INF;
        while (!pq.empty()) {
            Status now;
            
            do {
                now = pq.top();
                pq.pop();
                // cout << "test " << now.r << ' ' << now.c << ' ' << now.dir << ' ' << now.rotate << ' ' << now.val << endl;
            } while (vis[now.r][now.c][now.dir][now.rotate] and !pq.empty());
            
            if (vis[now.r][now.c][now.dir][now.rotate] and pq.empty())
                break;
            
            if (!count) {
                vis[now.r][now.c][now.dir][now.rotate] = true;
                _list[now.r][now.c][now.dir] = now.val;   
            } else count--;
            
            // cout << now.r << ' ' << now.c << ' ' << now.dir << ' ' << now.rotate << ' ' << now.val << endl;
            
            auto next = find_next(now);
            
            for (auto i : next) {
                if (i.val < _list[i.r][i.c][i.dir])
                    pq.emplace(i);
                
                if (i.r == tr and i.c == tc and i.rotate)
                    ans = min(ans, ll(i.val));
            }
        }
        
        if (ans == INF)
            cout << "Case " << C++ << ": Impossible" << endl;
        else 
            cout << "Case " << C++ << ": " << ans << endl;
    }
}