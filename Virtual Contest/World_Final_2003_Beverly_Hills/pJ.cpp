#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

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

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

inline int num(char ch) {
    return islower(ch) ? ch - 'a' + 26 : ch - 'A';
}

int cal(int src) {
    int ret = src;
    
    while (true) {
        int pay = 1 + (ret - 1) / 20;
        
        if (ret - pay >= src) break;
        ret++;
    }
    
    return ret;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (n == -1) break;
        
        deq<deq<bool>> _map(52, deq<bool>(52));
        for (int i = 0; i < n; i++) {
            char a, b;
            cin >> a >> b;
            
            int na = num(a), nb = num(b);
            
            _map[na][nb] = true;
            _map[nb][na] = true;
        }
        
        deq<bool> vis(52);
        vec<int> ans(52, INF);
        int need;
        char s, e;
        cin >> need >> s >> e;
        
        auto cmp = [](pii a, pii b) -> bool { return a.F > b.F; };
        priority_queue<pii, vec<pii>, decltype(cmp)> pq(cmp);
        
        ans[num(e)] = need;
        pq.emplace(need, num(e));
        
        while (!pq.empty()) {
            auto now = pq.top();
            pq.pop();
            
            if (vis[now.S])
                continue;
                
            vis[now.S] = true;
            
            for (int i = 0; i < 52; i++) {
                if (_map[now.S][i] and !vis[i]) {
                    if (now.S < 26) {   //* town.
                        int NEED = cal(ans[now.S]);
                        
                        if (NEED < ans[i]) {
                            ans[i] = NEED;
                            pq.emplace(ans[i], i);
                        }
                    } else { //* village
                        if (ans[now.S] + 1 < ans[i]) {
                            ans[i] = ans[now.S] + 1;
                            pq.emplace(ans[i], i);
                        }
                    }
                }
            }
        }
        
        cout << "Case " << c++ << ": " << ans[num(s)] << endl;
    }
}