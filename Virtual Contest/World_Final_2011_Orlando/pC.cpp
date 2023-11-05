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

deq<deq<bool>> G, vis;

int R, C;
int gx[4] = {0, -1, 0, 1};
int gy[4] = {1, 0, -1, 0};

inline bool clamp(int src, int l, int r) {
    return !(src >= l and src < r);
}

int dfs(p<int> pos, bool type) {
    int ret = 0;
    if (type) {
        queue<p<int>> que;
        que.emplace(pos);
        
        while (!que.empty()) {
            auto now = que.front();
            que.pop();
            
            if (vis[now.F][now.S]) continue;
            vis[now.F][now.S] = true;
            
            for (int i = 0; i < 4; i++) {
                if (clamp(now.F + gx[i], 0, R+2)) continue;
                if (clamp(now.S + gy[i], 0, 4*C+2)) continue;
                if (vis[now.F + gx[i]][now.S + gy[i]]) continue;
            
                if (!G[now.F+gx[i]][now.S+gy[i]]) {
                    ret++;
                    
                    queue<p<int>> black;
                    black.emplace(now.F+gx[i], now.S+gy[i]);
                    
                    while (!black.empty()) {
                        auto b_now = black.front();
                        black.pop();
                        
                        if (vis[b_now.F][b_now.S]) continue;
                        vis[b_now.F][b_now.S] = true;
                        
                        for (int k = 0; k < 4; k++) {
                            if (clamp(b_now.F + gx[k], 0, R+2)) continue;
                            if (clamp(b_now.S + gy[k], 0, 4*C+2)) continue;
                            if (vis[b_now.F + gx[k]][b_now.S + gy[k]]) continue;
                            
                            if (G[b_now.F+gx[k]][b_now.S+gy[k]]) continue;
                            
                            black.emplace(b_now.F+gx[k], b_now.S+gy[k]);
                        }
                    }
                } else {
                    que.emplace(now.F+gx[i], now.S+gy[i]);
                }
            }
        }
        
        return ret;
    } else {
        queue<p<int>> que;
        que.emplace(pos);
        
        while (!que.empty()) {
            auto now = que.front();
            que.pop();
            
            if (vis[now.F][now.S]) continue;
            vis[now.F][now.S] = true;
            
            for (int i = 0; i < 4; i++) {
                if (clamp(now.F + gx[i], 0, R+2)) continue;
                if (clamp(now.S + gy[i], 0, 4*C+2)) continue;
                if (vis[now.F + gx[i]][now.S + gy[i]]) continue;
                
                if (G[now.F+gx[i]][now.S+gy[i]]) continue;
                
                que.emplace(now.F+gx[i], now.S+gy[i]);
            }
        }
        
        return 0;
    }
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> R >> C) {
        if (!R) break;
        
        G.resize(R+2);
        vis.resize(R+2);
        for (int i = 0; i < R+2; i++) {
            G[i].clear();
            G[i].resize(4*C+2);
            
            vis[i].clear();
            vis[i].resize(4*C+2);
        }
            
        
        for (int i = 1; i <= R; i++) {
            string str;
            cin >> str;
            
            for (int k = 0; k < C; k++) {
                switch (str[k]) {
                    case '0':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 0;
                        break;
                    case '1':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 1;
                        break;
                    case '2':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 0;
                        break;
                    case '3':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 1;
                        break;
                    case '4':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 0;
                        break;
                    case '5':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 1;
                        break;
                    case '6':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 0;
                        break;
                    case '7':
                        G[i][4*k+1] = 0;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 1;
                        break;
                    case '8':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 0;
                        break;
                    case '9':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 1;
                        break;
                    case 'a':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 0;
                        break;
                    case 'b':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 0;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 1;
                        break;
                    case 'c':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 0;
                        break;
                    case 'd':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 0;
                        G[i][4*k+4] = 1;
                        break;
                    case 'e':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 0;
                        break;
                    case 'f':
                        G[i][4*k+1] = 1;
                        G[i][4*k+2] = 1;
                        G[i][4*k+3] = 1;
                        G[i][4*k+4] = 1;
                        break;
                }
            }
        }
        
        // devec2(G);
        
        dfs({0, 0}, false);
        // devec2(vis);
        
        vec<int> count(6);
        for (int i = 0; i < R+2; i++) {
            for (int k = 0; k < 4*C+2; k++) {
                if (vis[i][k]) continue;
                
                count[dfs({i, k}, true)]++;
                // devec2(vis);
            }
        }
        
        // devec(count);
        
        string str;
        for (int i = 0; i < 6; i++) 
            switch (i) {
                case 0:
                    str += string(count[i], 'W');
                    break;
                case 1:
                    str += string(count[i], 'A');
                    break;
                case 2:
                    str += string(count[i], 'K');
                    break;
                case 3:
                    str += string(count[i], 'J');
                    break;
                case 4:
                    str += string(count[i], 'S');
                    break;
                case 5:
                    str += string(count[i], 'D');
                    break;
            }
            
        sort(al(str));
        
        cout << "Case " << c++ << ": " << str << endl;
        
    }
}