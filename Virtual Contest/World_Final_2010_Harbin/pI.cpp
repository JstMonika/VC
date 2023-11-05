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

ll n, m, ans = 0;
deq<deq<bool>> vis;
vec<int> cx(3), cy(3), t(3);

void dfs(int x, int y, int now) {
    if (x == 0 and y == 1 and now == n*m) {
        ans++;
        return;
    } else if (x == 0 and y == 1)
        return;
    
    //* cut.
    for (int i = 0; i < 3; i++) {
        if (now == t[i] and !(x == cx[i] and y == cy[i]))
            return;
        
        if (now < t[i]) {
            if (t[i] - now < abs(x - cx[i]) + abs(y - cy[i]))
                return;
        }
    }
    
    int gx[4] = {0, 1, 0, -1};
    int gy[4] = {1, 0, -1, 0};
    for (int i = 0; i < 4; i++) {
        int nx = x + gx[i], ny = y + gy[i];
        
        if (nx < 0 or nx >= n) continue;
        if (ny < 0 or ny >= m) continue;
        
        if (!vis[nx][ny]) {
            int _size = 0;
            
            deq<deq<bool>> exist(n, deq<bool>(m));
            queue<p<int>> que;
            exist[x][y] = true;
            que.emplace(nx, ny);
            
            int tx, ty;
            while (!que.empty()) {
                tie(tx, ty) = que.front();
                que.pop();
                
                if (exist[tx][ty])
                    continue;
                    
                exist[tx][ty] = true;
                _size++;
                
                for (int k = 0; k < 4; k++) {
                    int nnx = tx + gx[k], nny = ty + gy[k];
                    
                    if (nnx < 0 or nnx >= n) continue;
                    if (nny < 0 or nny >= m) continue;
                    
                    if (!exist[nnx][nny] and !vis[nnx][nny])
                        que.emplace(nnx, nny);
                }
            }
            
            if (now + _size != n*m) {
                // devec2(vis);
                // cout << x << ' ' << y << endl;
                return;
            }
            
            break;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            if (vis[i][k]) continue;
            if (i == 0 and k == 1) continue;
            
            int count = 0;
            
            for (int z = 0; z < 4; z++) {
                int nx = i + gx[z], ny = k + gy[z];
                
                if (nx < 0 or nx >= n) continue;
                if (ny < 0 or ny >= m) continue;
                
                if (!vis[nx][ny])
                    count++;
            }
            
            if (count <= 1) {
                if (i != x or k != y) {
                    // devec2(vis);
                    // cout << "next: " << x << ' ' << y << ", ";
                    // cout << i << ' ' << k << endl;
                    return;
                }
            }
        }
    }
    
    vis[x][y] = true;
    
    for (int i = 0; i < 4; i++) {
        int nx = x + gx[i], ny = y + gy[i];
        
        if (nx < 0 or nx >= n) continue;
        if (ny < 0 or ny >= m) continue;
    
        if (!vis[nx][ny])
            dfs(nx, ny, now + 1);
    }
    
    vis[x][y] = false;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        ans = 0;
        
        vis.resize(n);
        for (auto &i : vis)
            i.resize(m), fill(al(i), 0);
        
        for (int i = 0; i < 3; i++) {
            cin >> cx[i] >> cy[i];
            t[i] = n * m * (i+1) / 4;
        }
        
        dfs(0, 0, 1);
        
        cout << "Case " << c++ << ": " << ans << endl;
    }
}