#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

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

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n, m;
        cin >> n >> m;
        
        deq<deq<bool>> _list(n, deq<bool>(m));
        int zero = 0;
        
        for (int i = 0; i < n; i++) {
            cin.get();
            for (int k = 0; k < m; k++) {
                _list[i][k] = cin.get() - '0';
                if (_list[i][k] == 0) zero++;
            }
        }
        
        bool good = false;
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < m; k++) {
                int count = 0;
                
                for (int pi = -1; pi <= 1; pi++) {
                    for (int pk = -1; pk <= 1; pk++) {
                        if (pi == 0 and pk == 0) continue;
                        if (i+pi < 0 or i+pi >= n) continue;
                        if (k+pk < 0 or k+pk >= m) continue;
                        
                        if (_list[i+pi][k+pk] == 0) count++;
                    }
                }
                
                if (count >= 1 and _list[i][k] == 0) {
                    good = true;
                }
            }
        }
        
        // devec2(_list);
        // cout << zero << ' ' << good << endl;
        if (good) {
            cout << m*n - zero << endl;
        } else if (!good and zero) {
            cout << m*n - zero - 1 << endl;
        } else {
            cout << m*n - 2 << endl;
        }
    }
}