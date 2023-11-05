#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

double eps = 1e-9;
double PI = acos(-1);

int main()
{
    yccc;
    
    int c = 1;
    int a1, b1, t1, a2, b2, t;
    while (cin >> a1 >> b1 >> t1 >> a2 >> b2 >> t) {
        if (a1 == 0) break;
        
        double t2 = sqrt(1.*t1*t1*a2*a2*a2/a1/a1/a1), c2 = sqrt(a2 * a2 - b2 * b2), tmp;
        t2 = modf(t / t2, &tmp);
        
        double target = a2 * b2 * PI * t2;
        
        double L = -a2, R = a2;
        if (t2 >= 0.5) {
            // cout << "here?";
            while (R - L > eps) {
                double M = (L+R) / 2;
                double now = a2 * b2 * (2*PI - acos(M / a2)) / 2;
                double y = sin(acos(M / a2)) * b2;
                
                // cout << now + (c2 * y / 2) << ' ' << target << endl;
                if (now + (c2 * y / 2) < target) {
                    L = M;
                } else {
                    R = M;
                }
            }
        } else {
            while (R - L > eps) {
                double M = (L+R) / 2;
                double now = a2 * b2 * acos(M / a2) / 2;
                double y = sin(acos(M / a2)) * b2;
                
                // cout << y << ' ' << c2 << endl;
                // cout << now << ' ' << (c2 * y / 2) << ' ' << target << endl;
                if (now - (c2 * y / 2) < target) {
                    R = M;
                } else {
                    L = M;
                }
            }
        }
        
        cout << "Solar System " << c++ << ": " << fixed << setprecision(3)
             << L << ' ' << (t2 >= 0.5 ? -1 : 1) * sin(acos(L / a2)) * b2 << endl;
    }
    
    
}