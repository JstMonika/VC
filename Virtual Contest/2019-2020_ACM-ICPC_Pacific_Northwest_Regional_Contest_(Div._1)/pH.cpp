#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

inline double fcmp(double a, double b = 0, double eps = 1e-13) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);

struct node {
    double T, s, a;
};

int main() {
    yccc;
    
    int n;
    cin >> n;
    
    vec<node> _list(n);
    for (auto &i : _list) {
        cin >> i.T >> i.s >> i.a;
    }
    
    double ans = 0, tmp = 0;
    double deg = 0.0;
    for (int k = 0; k < n; k++)
    {
        double tmp = 0;
        deg = _list[k].a;

        for (auto &i : _list) {
            double rad = i.a - deg;
            if (fcmp(rad) < 0) rad += 2 * PI;
            if (fcmp(rad, PI) > 0) rad = 2 * PI - rad;
            
            tmp += max(0., i.T - i.s * rad);
        }
        
        ans = max(ans, tmp);
    }

    cout << fixed << setprecision(9) << ans << endl;
}