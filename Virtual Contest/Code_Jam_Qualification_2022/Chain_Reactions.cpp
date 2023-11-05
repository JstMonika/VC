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

int main()
{
    yccc;
    
    int t, c = 1;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        vec<ll> val(n);
        vec<int> parent(n);
        vec<vec<int>> G(n);
        vec<int> point(n);
        
        for (auto &i : val)
            cin >> i;
            
        for (int i = 0; i < n; i++) {
            cin >> parent[i];
            parent[i]--;
            
            if (parent[i] >= 0) {
                G[parent[i]].eb(i);
                point[parent[i]]++;
            }
        }
        
        ll vans = 0;
        queue<int> que;
        for (int i = 0; i < n; i++)
            if (point[i] == 0) que.emplace(i);
            
        while (!que.empty()) {
            auto now = que.front();
            que.pop();
            
            ll _min = llINF;
            
            for (int i = 0; i < G[now].size(); i++) {
                _min = min(_min, val[G[now][i]]);
            }
            
            bool first = true;
            for (int i = 0; i < G[now].size(); i++) {
                if (val[G[now][i]] == _min and first) {
                    first = false;
                    continue;
                }
                else {
                    vans += val[G[now][i]];
                    // cout << "select: " << G[now][i]+1 << endl;
                }
            }
            
            if (_min != llINF)
                val[now] = max(_min, val[now]);
            
            // cout << now+1 << ": " << val[now] << endl;
            
            if (parent[now] < 0) {
                vans += val[now];
                // cout << "select: " << now+1 << endl;
            } else if (--point[parent[now]] == 0)
                que.emplace(parent[now]);
        }
        
        cout << "Case #" << c++ << ": " << vans << endl;
    }
}