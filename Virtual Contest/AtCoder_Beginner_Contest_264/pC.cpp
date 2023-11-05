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
    
    int n, m;
    cin >> n >> m;
    vec<vec<int>> _list(n, vec<int>(m));
    for (auto &i : _list)
        for (auto &k : i)
            cin >> k;
    
    int n2, m2;
    cin >> n2 >> m2;
    vec<vec<int>> copy(n2, vec<int>(m2));
    for (auto &i : copy)
        for (auto &k : i)
            cin >> k;
    
    if (n2 > n or m2 > m) {
        cout << "No";
        return 0;
    }
    
    string str = string(n-n2, '0') + string(n2, '1');
    string str2 = string(m-m2, '0') + string(m2, '1');
    
    bool good = true;
    do {
        do {
            good = true;
            int I = 0, J = 0;
            for (int i = 0; i < n; i++) {
                if (str[i] == '0') continue;
                
                for (int k = 0; k < m; k++) {
                    if (str2[k] == '0') continue;
                    
                    if (_list[i][k] != copy[I][J]) {
                        // cout << i << ' ' << k << ' ' << I << ' ' << J << endl;
                        good = false;
                        break;
                    }
                    
                    J++;
                }
                
                I++, J = 0;
            }
            
            if (good) {
                cout << "Yes";
                return 0;
            }
        } while (next_permutation(al(str)));
    } while (next_permutation(al(str2)));
    
    cout << (good ? "Yes" : "No");
}