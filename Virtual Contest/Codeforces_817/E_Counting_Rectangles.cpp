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

struct Rect {
    int x, y;
    
    Rect() {}
};

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n, q;
        cin >> n >> q;
        
        vec<vec<ll>> pre(1001, vec<ll>(1001));
        vec<Rect> _list(n);
        for (auto &i : _list) {
            cin >> i.x >> i.y;
            
            pre[i.x][i.y]++;
        }
        
        for (int i = 1; i <= 1000; i++) {
            for (int k = 1; k <= 1000; k++) {
                pre[i][k] = i * k * pre[i][k];
                pre[i][k] += pre[i-1][k] + pre[i][k-1] - pre[i-1][k-1];
            }
        }
        
        // for (int i = 1; i <= 3; i++) {
        //     for (int k = 1; k <= 3; k++)
        //         cout << pre[i][k] << " \n"[k == 3];
        // }
        
        auto cmp = [](Rect& a, Rect& b) {
            if (a.x != b.x) return a.x < b.x;
            
            return a.y > b.y;
        };
        
        sort(al(_list), cmp);
        
        for (int i = 0; i < q; i++) {
            Rect s, b;
            cin >> s.x >> s.y >> b.x >> b.y;
            
            cout << pre[b.x-1][b.y-1] - pre[s.x][b.y-1] - pre[b.x-1][s.y] + pre[s.x][s.y] << endl;
        }
    }
}