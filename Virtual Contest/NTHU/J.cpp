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

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    vec<int> cage(n+1);
    for (int i = 1; i <= n; i++)
        cin >> cage[i];
    
    vec<vec<int>> _map(9, vec<int>(9));
    auto num = _map;
    
    for (auto &i : _map)
        for (auto &k : i)
            cin >> k;
    
    for (int i = 0; i < 9; i++)
        for (int k = 0; k < 9; k++) {
            cin >> num[i][k];
            
            cage[_map[i][k]] -= num[i][k];
        }
        
    if (any_of(al(cage), [](int i){ return i != 0; })) {
        cout << "NO\n";
        return 0;
    }
    
    devec(cage);
    
    for (int i = 0; i < 9; i++) {
        deq<bool> vis(10);
        for (int k = 0; k < 9; k++) {
            if (vis[num[i][k]]) {
                cout << "NO\n";
                return 0;
            }
            vis[num[i][k]] = true;
        }
        
        fill(al(vis), false);
        for (int k = 0; k < 9; k++) {
            if (vis[num[k][i]]) {
                cout << "NO\n";
                return 0;
            }
            vis[num[k][i]] = true;
        }
        
        fill(al(vis), false);
        for (int k = 0; k < 9; k++) {
            if (vis[num[i/3*3+k/3][(i%3)*3+(k%3)]]) {
                cout << "NO\n";
                return 0;
            }
            vis[num[i/3*3+k/3][(i%3)*3+(k%3)]] = true;
        }
    }
    
    cout << "YES\n";
}