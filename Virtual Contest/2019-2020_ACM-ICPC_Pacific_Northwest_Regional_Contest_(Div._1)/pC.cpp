#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);

int main() {
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    vec<p<int>> _list(m);
    for (auto &i : _list) {
        cin >> i.F >> i.S;
        i.F--;
        i.S--;
    }
    
    vec<vec<int>> G(n);
    for (auto i : _list) {
        G[i.F].eb(i.S);
        G[i.S].eb(i.F);
    }
    
    vec<int> vis(n, -1);
    queue<int> now, prev;
    now.emplace(0);
    
    int count = 0;
    while (now.size()) {
        prev = now;
        now = queue<int>();
        
        while (prev.size()) {
            auto next = prev.front();
            prev.pop();
            
            if (vis[next] != -1) continue;
            vis[next] = count;
            
            for (auto i : G[next]) {
                if (vis[i] == -1) {
                    now.emplace(i);
                }
            }
        }
        
        count++;
    }
    
    cout << vis[n-1]-1 << endl;
}