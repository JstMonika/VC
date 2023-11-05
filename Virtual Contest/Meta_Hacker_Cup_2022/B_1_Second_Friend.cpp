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

int main()
{
    yccc;
    
    int n, c = 1;
    cin >> n;
    
    while (n--) {
        int R, C;
        cin >> R >> C;
        
        bool e = true;
        string s;
        for (int i = 0; i < R; i++) {
            cin >> s;
            
            if (any_of(al(s), [](char ch) { return ch == '^'; })) e = false;
        }
        
        if ((R == 1 or C == 1) and !e) {
            cout << "Case #" << c++ << ": Impossible" << endl;
        } else {
            cout << "Case #" << c++ << ": Possible" << endl;
            
            for (int i = 0; i < R; i++)
                cout << string(C, (R == 1 or C == 1 ? '.' : '^')) << endl;
        }
    }
}