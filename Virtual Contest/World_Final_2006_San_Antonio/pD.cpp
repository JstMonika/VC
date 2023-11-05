#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifdef dbg
#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#endif

#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

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
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int n;
    while (cin >> n) {
        vec<vec<int>> _list(n);
        
        vec<p<int>> mod(9);
        for (int i = 1; i <= 9; i++) {
            map<int, int> pos;
            int idx = 0, len = 1, m = i % n;
            
            do {
                pos[m] = idx++;
                
                (m = (m * 10) + i) %= n;
            } while ();
        }
    }
}