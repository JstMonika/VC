#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifdef dbg
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#else
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
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
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int n, m;
vec<vec<pair<ll, ll>>> G;
vec<int> pa;

bool find_path() {
    vec<vec<int>> parent(n+m+2, vec<int>(n+m+2));
    vec<vec<ll>> dis(n+m+2, vec<ll>(n+m+2, llINF));
    for (int i = 0; i < n+m+2; i++)
        for (int k = 0; k < n+m+2; k++) {
            dis[i][k] = (G[i][k].F > 0 ? G[i][k].S : llINF);
            
            if (G[i][k].S != llINF)
                parent[i][k] = i;
                
            // cout << G[i][k].F << " \n"[k == n+m+1];
        }
    
    
    for (int i = 0; i < n+m+2; i++)
        for (int k = 0; k < n+m+2; k++)
            for (int j = 0; j < n+m+2; j++) {
                if (dis[i][j] == llINF or dis[k][i] == llINF)
                    continue;
                
                if (dis[k][i] + dis[i][j] < dis[k][j]) {
                    // printf("dis[%d][%d] = dis[%d][%d] + dis[%d][%d] <- %ld = %ld + %ld\n", k, j, k, i, i, j, dis[k][j], dis[k][i], dis[i][j]);
                    // fflush(stdout);
                    dis[k][j] = dis[k][i] + dis[i][j];
                    parent[k][j] = parent[i][j];
                    
                }
            }
    // cout << dis[3][7] << ' ' << dis[7][5] << ' ' << dis[3][5] << endl;
    // cout << dis[0][5] << ' ' << dis[5][6] << ' ' << dis[0][6] << endl;
    
    if (dis[0][n+m+1] != llINF) {
        pa.clear();
        
        int now = n+m+1;
        while (parent[0][now] != 0) {
            pa.eb(now);
            now = parent[0][now];
            // cout << now << endl;
        }
        
        pa.eb(now);
        pa.eb(0);
        reverse(al(pa));
        
        devec(pa);
        
        return true;
    }
    
    return false;
}

int main()
{
    #ifdef dbg
    cout << "DEBUG ON" << endl;
    #endif
    
    yccc;
    
    int c = 1;
    while (cin >> n >> m) {
        if (n == 0) break;
        
        vec<int> nNum(n), mNum(m);
        for (auto &i : nNum)
            cin >> i;
        for (auto &i : mNum)
            cin >> i;
        
        //* 0, 1~n, n+1~n+m, n+m+1
        G.clear();
        G.resize(n+m+2);
        for (auto &i : G)
            i.resize(n+m+2);
        
        for (int i = 1; i <= n; i++)
            G[0][i] = make_pair(nNum[i-1], 0);
        for (int i = n+1; i <= n+m; i++)
            G[i][n+m+1] = make_pair(mNum[i-(n+1)], 0);
            
        for (int i = 1; i <= n; i++) {
            for (int k = n+1; k <= n+m; k++) {
                double tmp;
                cin >> tmp;
                
                tmp *= 100;
                
                G[i][k] = make_pair(llINF, (!fcmp(tmp, -100) ? llINF : ll(tmp+eps)));
                G[k][i] = make_pair(0, (!fcmp(tmp, -100) ? llINF : -ll(tmp+eps)));
            }
        }
        
        auto tmpG = G;
        
        while (find_path()) {
            ll _min = llINF;
            for (int i = 0; i < pa.size() - 1; i++) {
                _min = min(_min, G[pa[i]][pa[i+1]].F);
            }
            
            for (int i = 0; i < pa.size() - 1; i++) {
                G[pa[i]][pa[i+1]].F -= _min;
                G[pa[i+1]][pa[i]].F += _min;
            }
        }
        
        long long min_cost = 0;
        for (int i = n+1; i <= n+m; i++) {
            for (int k = 1; k <= n; k++) {
                min_cost += G[i][k].F * G[k][i].S;
            }
        }
        
        G = tmpG;
        
        for (int i = 1; i <= n; i++)
            G[0][i].S = 0;
        for (int i = n+1; i <= n+m; i++)
            G[i][n+m+1].S = 0;
            
        for (int i = 1; i <= n; i++)
            for (int k = n+1; k <= n+m; k++)
                if (G[i][k].S != llINF) {
                    G[i][k].S = INF - G[i][k].S;
                    G[k][i].S = -G[i][k].S;
                }
        
        // cout << "-> " << G[7][5].S << ' ' << G[5][7].S << endl;
        // cout << "-----\n";
        while (find_path()) {
            ll _min = llINF;
            for (int i = 0; i < pa.size() - 1; i++) {
                _min = min(_min, G[pa[i]][pa[i+1]].F);
            }
            
            for (int i = 0; i < pa.size() - 1; i++) {
                G[pa[i]][pa[i+1]].F -= _min;
                G[pa[i+1]][pa[i]].F += _min;
            }
        }
        
        long long max_cost = 0;
        for (int i = n+1; i <= n+m; i++) {
            for (int k = 1; k <= n; k++) {
                max_cost += G[i][k].F * (INF-G[k][i].S);
            }
        }
        
        cout << "Problem " << c++ << ": ";
        cout << fixed << setprecision(2) << 1. * min_cost / 100;
        cout << " to ";
        cout << fixed << setprecision(2) << 1. * max_cost / 100 << endl;
    }
}