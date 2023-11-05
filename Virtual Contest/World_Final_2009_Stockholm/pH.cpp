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

deq<deq<bool>> G;

deq<bool> vis(10000);
bool dfs(int now, int e) {
    if (now == e) return true;
    vis[now] = true;
    
    for (int i = 0; i < G[now].size(); i++) {
        if (G[now][i] and !vis[i]) {
            
            bool ret = dfs(i, e);
            
            if (ret)
                return true;
        }
    }
    
    return false;
}

int main()
{
    yccc;
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        vec<char> result(n);
        
        G.clear();
        G.resize(2*n);
        for (auto &i : G)
            i.resize(2*n);
        
        for (int i = 0; i < m; i++) {
            int num;
            cin >> num;
            
            vec<pair<char, int>> _list(num);
            for (auto &k : _list) {
                cin >> k.S >> k.F;
                k.S--;
            }
                
            if (num <= 2) {
                for (auto k : _list)
                    if (k.F == 'y')  G[k.S*2+1][k.S*2] = true;
                    else G[k.S*2][k.S*2+1] = true;
            } else {
                for (int r = 0; r < num; r++)
                    for (int s = r+1; s < num; s++) {
                        int fi, se;
                        fi = (_list[r].F == 'y' ? _list[r].S * 2 : _list[r].S * 2 + 1);
                        se = (_list[s].F == 'y' ? _list[s].S * 2 : _list[s].S * 2 + 1);
                        
                        G[fi^1][se] = G[se^1][fi] = true;
                    }
            }
        }
        
        cout << "Case " << c++ << ": ";
        bool good = true;
        for (int i = 0; i < n; i++) {
            fill(al(vis), false);
            bool fi = dfs(2*i, 2*i+1);
            fill(al(vis), false);
            bool se = dfs(2*i+1, 2*i);
            
            if (fi and se) {
                good = false;
                break;
            } else if (fi) result[i] = 'n';
            else if (se) result[i] = 'y';
            else result[i] = '?';
        }
        
        if (good) {
            for (auto i : result) cout << i;
            cout << endl;
        } else cout << "impossible\n";
    }
}