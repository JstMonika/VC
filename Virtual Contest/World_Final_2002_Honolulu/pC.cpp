#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<typename T> using vec = vector<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct Node {
    double x, y;
    
    double dis(Node src) {
        double dx = x - src.x, dy = y - src.y;
        return sqrt(dx * dx + dy * dy);
    }
};

using pid = pair<int, double>;

int main()
{
    yccc;
    
    int n, cap, c = 1;
    while (cin >> n >> cap) {
        if (!n) break;
        
        vec<Node> _list(n);
        vec<vec<double>> G(n, vec<double>(n, 1e11));
        for (auto &i : _list)
            cin >> i.x >> i.y;
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < i; k++)
                if (_list[i].dis(_list[k]) <= 1.0 * cap / 2)
                    G[i][k] = G[k][i] = _list[i].dis(_list[k]);
        
        deque<bool> vis(n);
        vec<double> val(n, 1e11);
        
        auto cmp = [](pid a, pid b) { return a.S > b.S; };
        priority_queue<pid, vec<pid>, decltype(cmp)> pq(cmp);
        
        pq.emplace(n-1, 0);
        
        while (!pq.empty()) {
            auto now = pq.top();
            pq.pop();
            
            if (vis[now.F])
                continue;
                
            // cout << "set " << now.F << " to " << now.S << endl;
            val[now.F] = now.S;
            vis[now.F] = true;
            
            for (int i = 0; i < n; i++) {
                if (G[now.F][i] != 1e11) {
                    if (val[now.F] <= cap - G[now.F][i] * 2) {
                        // cout << "emplace from " << now.F << " to " << i << endl;
                        pq.emplace(i, G[now.F][i] + val[now.F]);
                    } else {
                        if (cap - G[now.F][i] * 3 > 0) {
                            double times = ceil((val[now.F] - (cap - G[now.F][i] * 2)) / (cap - G[now.F][i] * 3));
                            
                            // cout << "emplace from " << now.F << " to " << i << ", times: " << times << endl;
                            pq.emplace(i, G[now.F][i] + (val[now.F] - times * (cap - G[now.F][i] * 3)) + (times * (cap - G[now.F][i])));
                        }
                    }
                }
            }
        }
        
        if (val[0] == 1e11) {
            cout << "Trial " << c++ << ": Impossible\n\n";
        } else {
            if (val[0] > 1000000) {
                cout << "Trial " << c++ << ": Impossible\n\n";
            } else {
                cout << "Trial " << c++ << ": " << int(ceil(val[0])) << " units of food\n\n";
            }
        }
    }
}