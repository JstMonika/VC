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
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n, m, w, ans;
vec<p<int>> pos(10), hole(10);
map<vec<vec<int>>, int> _set;
//* left, up, right, down.
map<p<int>, int> _map;

bool empty(vec<vec<int>> now) {
    for (int i = 0; i < n; i++)
        for (int k = 0; k < n; k++)
            if (now[i][k] != -1) return false;
    return true;
}

void go(vec<vec<int>> now, deq<deq<bool>> prev_s, int step) {
    if (empty(now)) {
        ans = min(ans, step);
        return;
    }
    
    devec2(now);
    devec2(prev_s);
    
    //* down.
    auto next = now;
    auto solid = prev_s;
    bool good = true;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (next[i][k] != -1) {
                int tk = k;
                
                while ((_map[make_pair(i, tk)] & 1) == 0 and tk-1 >= 0 and next[i][tk-1] == -1 and solid[i][tk]) tk--;
                swap(next[i][k], next[i][tk]);
                if (make_pair(i, tk) == hole[next[i][tk]]) {
                    next[i][tk] = -1;
                    solid[i][tk] = true;
                } else if (solid[i][tk] == false)
                    good = false;
            }
        }
    }
    
    devec2(next);
    debug(good);
    
    if (good and (_set.find(next) == _set.end() or _set[next] > step+1 or empty(next))) {
        
        _set[next] = step+1;
        go(next, solid, step+1);
    }
    
    //* up.
    next = now;
    solid = prev_s;
    good = true;
    for (int i = 0; i < n; i++) {
        for (int k = n-1; k >= 0; k--) {
            if (next[i][k] != -1) {
                int tk = k;
                
                while ((_map[make_pair(i, tk)] & (1<<2)) == 0 and tk+1 < n and next[i][tk+1] == -1 and solid[i][tk]) tk++;
                swap(next[i][k], next[i][tk]);
                if (make_pair(i, tk) == hole[next[i][tk]]) {
                    next[i][tk] = -1;
                    solid[i][tk] = true;
                } else if (solid[i][tk] == false)
                    good = false;
            }
        }
    }
    
    devec2(next);
    debug(good);
    
    if (good and (_set.find(next) == _set.end() or _set[next] > step+1 or empty(next))) {
        
        _set[next] = step+1;
        go(next, solid, step+1);
    }
    
    //* left.
    next = now;
    solid = prev_s;
    good = true;
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (next[i][k] != -1) {
                int ti = i;
                
                while ((_map[make_pair(ti, k)] & (1<<3)) == 0 and ti-1 >= 0 and next[ti-1][k] == -1 and solid[ti][k]) ti--;
                swap(next[i][k], next[ti][k]);
                if (make_pair(ti, k) == hole[next[ti][k]]) {
                    next[ti][k] = -1;
                    solid[ti][k] = true;
                } else if (solid[ti][k] == false)
                    good = false;
            }
        }
    }
    
    devec2(next);
    debug(good);
    
    if (good and (_set.find(next) == _set.end() or _set[next] > step+1 or empty(next))) {
        
        _set[next] = step+1;
        go(next, solid, step+1);
    }
    
    //* right.
    next = now;
    solid = prev_s;
    good = true;
    for (int k = 0; k < n; k++) {
        for (int i = n-1; i >= 0; i--) {
            if (next[i][k] != -1) {
                int ti = i;
                
                while ((_map[make_pair(ti, k)] & (1<<1)) == 0 and ti+1 < n and next[ti+1][k] == -1 and solid[ti][k]) ti++;
                swap(next[i][k], next[ti][k]);
                if (make_pair(ti, k) == hole[next[ti][k]]) {
                    next[ti][k] = -1;
                    solid[ti][k] = true;
                } else if (solid[ti][k] == false)
                    good = false;
            }
        }
    }
    
    devec2(next);
    debug(good);
    
    if (good and (_set.find(next) == _set.end() or _set[next] > step+1 or empty(next))) {
        
        _set[next] = step+1;
        go(next, solid, step+1);
    }
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n >> m >> w) {
        if (!n) break;
        
        ans = INF;
        _set.clear();
        _map.clear();
        
        deq<deq<bool>> solid(4, deq<bool>(4, true));
        
        for (int i = 0; i < m; i++)
            cin >> pos[i];
        for (int i = 0; i < m; i++) {
            cin >> hole[i];
            solid[hole[i].F][hole[i].S] = false;
        }
            
        p<int> from, to;
        for (int i = 0; i < w; i++) {
            cin >> from >> to;
            
            if (from.S > to.S) {
                _map[from] += (1<<0);
                _map[to] += (1<<2);
            }
            else if (from.S < to.S) {
                _map[from] += (1<<2);
                _map[to] += (1<<0);
            }
            else if (from.F > to.F) {
                _map[from] += (1<<3);
                _map[to] += (1<<1);
            }
            else {
                _map[from] += (1<<1);
                _map[to] += (1<<3);
            }
        }
        
        vec<vec<int>> init(n, vec<int>(n, -1));
        
        devec(pos);
        devec(hole);
        devec2(solid);
        
        for (int i = 0; i < m; i++) {
            if (pos[i] != hole[i])
                init[pos[i].F][pos[i].S] = i;
        }
        
        _set[init] = 0;
        go(init, solid, 0);
        
        cout << "Case " << c++ << ": " << (ans == INF ? "impossible" : to_string(ans) + " moves") << endl << endl;
    }
}