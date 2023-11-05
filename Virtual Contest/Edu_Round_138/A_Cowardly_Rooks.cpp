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

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

bool check(vec<p<int>> _list, int n) {
    for (int i = 0; i < _list.size(); i++) {
        for (int k = i+1; k < _list.size(); k++) {
            if (_list[i].F == _list[k].F or _list[i].S == _list[k].S) return false;
        }
    }
    
    return true;
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        int n, m;
        cin >> n >> m;
        
        vec<p<int>> _list(m);
        for (auto &i : _list)
            cin >> i.F >> i.S;
            
        bool good = false;
        for (int i = 0; i < n; i++) {
            int gx[4] = {0, -1, 0, 1};
            int gy[4] = {1, 0, -1, 0};
            
            for (int k = 0; k < 4; k++) {
                if (_list[i].F + gx[k] <= 0 or _list[i].F + gx[k] > n) continue;    
                if (_list[i].S + gy[k] <= 0 or _list[i].S + gy[k] > n) continue;
                
                p<int> tmp = _list[i];
                
                _list[i].F += gx[k];
                _list[i].S += gy[k];
                
                if (check(_list, n)) {
                    // for (auto z : _list) {
                    //     cout << z.F << " " << z.S << endl;
                    // }
                    cout << "YES\n";
                    good = true;
                    break;
                }
                
                _list[i] = tmp;
            }
            
            if (good) break;
        }
        
        if (!good) cout << "NO\n";
    }
}