#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifdef dbg
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#endif

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

int main()
{
    yccc;
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        if (!n) break;
        
        int idx = 0;
        map<string, int> name;
        deq<deq<bool>> _map(n, deq<bool>(n));
        
        for (int i = 0; i < m; i++) {
            string one, two;
            cin >> one >> two;
            
            if (name.find(one) == name.end())
                name[one] = idx++;
            if (name.fine(two) == name.end())
                name[two] = idx++;
                
            _map[name[one]][name[two]] = _map[name[two]][name[one]] = true;
        }
        
        deq<bool> vis(n);
        queue<int> que;
        vis[0] = true;
        que.emplace(0);
        
        while (!que.empty()) {
            auto now = que.front();
            que.pop();
            
            for (int i = 0; i < n; i++)
                if (_map[now][i] and !vis[i]) {
                    vis[i] = true;
                    que.emplace(i);
                }   
        }
        
        if (any_of(al(vis), [](bool i){ return i == false; }))
            cout << "Network " << c++ << ": DISCONNECTED\n\n";
        
        vec<vec<int>> dis(n, vec<int>(n));
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                dis[i][k] = (_map[i][k] ? 1 : INF);
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                for (int j = 0; j < n; j++)
                    if (dis[i][j] + dis[j][k] < dis[i][k])
                        dis[i][k] = dis[i][j] + dis[j][k];
        
        int ans = 0;
        for (int i = 0; i < n; i++)
            for (int k = i+1; k < n; k++)
                ans = max(ans, dis[i][k]);
                
        cout << "Network " << c++ << ": " << ans << endl << endl;
    }
}