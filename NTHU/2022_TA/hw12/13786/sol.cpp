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
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n, x, d;
vec<int> _list;
int ans = 0;
vec<vec<int>> G;

int go(int now, int prev) {
    int sum = 0;
    
    for (int i = 1; i <= n; i++) {
        if (prev != i and G[now][i]) {
            sum += go(i, now);
        }
    }
    
    sum += _list[now-1];
    
    if (now == x) ans = sum;
    
    // cout << now << ": " << sum << endl;
    
    return sum;
}

int main()
{
    yccc;
    
    cin >> n >> x;
    
    _list.resize(n);
    for (auto &i : _list) {
        cin >> i;
    }
    
    G.assign(n+1, vec<int>(n+1));
    for (int i = 0; i < n-1; i++) {
        int s, e;
        cin >> s >> e;
        
        G[s][e] = G[e][s] = 1;
    }
    
    go(1, -1);
    cout << ans << endl;
}