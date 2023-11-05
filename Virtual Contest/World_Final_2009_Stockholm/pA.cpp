#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifdef dbg
#define endl '\n'
#endif

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
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

    int n, c = 1;
    while (cin >> n) {
        if (!n)
            break;

        vec<p<int>> _list(n);
        for (auto &i : _list)
            cin >> i.F >> i.S;
        

        double L = 0, R = 1500;
        while (fcmp(R, L) != 0) {
            double M = (L+R) / 2;

            vec<int> order(n);
            for (int i = 0; i < n; i++) order[i] = i;
            
            bool valid = false;
            do {
                bool good = true;
                double now = _list[order[0]].F;

                for (int k = 1; k < n; k++) {
                    if (_list[order[k]].S < now + M) {
                        good = false;
                        break;
                    }
                    
                    now = max(now + M, double(_list[order[k]].F));
                }

                if (good) {
                    valid = true;
                    break;
                }
            } while (next_permutation(al(order)));

            if (valid)
                L = M;
            else 
                R = M;
        }
        
        int m = int(R);
        int s = round((R - int(R)) * 60);

        if (s == 60)
            m++, s = 0;

        cout << "Case " << c++ << ": " << m << ":" << setw(2) << setfill('0') << s << endl;
    }
}
