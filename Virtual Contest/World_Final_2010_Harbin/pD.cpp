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

vec<p<int>> _list;
vec<vec<int>> G;

p<int> dfs(int parent, int now) {
    vec<p<int>> val;
    for (int i = 0; i < G[now].size(); i++) {
        if (G[now][i] == parent) continue;
        
        val.eb(dfs(now, G[now][i]));
    }
    
    auto cmp = [](p<int> a, p<int> b) {
        return (a.F - a.S) > (b.F - b.S);
    };
    sort(al(val), cmp);
    
    int a = _list[now].F, b = _list[now].S;
    for (auto i : val) {
        a = max(a, b + i.F);
        b += i.S;
    }
    
    return {a, b};
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        _list.resize(n);
        G.resize(n);
        for (auto &i : G)
            i.clear();
        
        for (auto &i : _list) {
            int t;
            cin >> i.F >> i.S >> t;
            i.S += t;
            
            i.F = max(i.F, i.S);
        }
        
        for (int i = 0; i < n-1; i++) {
            int s, e;
            cin >> s >> e;
            G[s-1].eb(e-1);
            G[e-1].eb(s-1);
        }
        
        int ans = INF;
        for (int i = 0; i < n; i++) {
            ans = min(ans, dfs(-1, i).F);
        }
        
        cout << "Case " << c++ << ": " << ans << endl;
    }
}