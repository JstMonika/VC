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

double cal(vec<double> a, double upper, double lower) {
    double ret = 0;
    
    double u = 1, l = 1;
    for (int i = 0; i < a.size(); i++) {
        ret += a[i] * (u-l);
        
        u *= upper;
        l *= lower;
    }
    
    return ret;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        vec<double> _list(n+1);
        for (auto &i : _list) {
            cin >> i;
        }
        
        double prev, o_prev, next, top, volume;
        cin >> prev >> top >> volume;
        o_prev = prev;
        
        vec<double> total(2*n+2);
        for (int i = 0; i <= n; i++)
            for (int k = 0; k <= n; k++)
                total[i+k] += _list[i] * _list[k];
        
        for (auto &i : total)
            i *= PI;
            
        for (int i = 2*n+1; i > 0; i--) {
            total[i] = total[i-1] / i;
        }
        
        vec<double> ans;
        while (true) {
            double L = prev, R = top, M;
            
            if (ans.size() == 8) break;
            if (fcmp(cal(total, R, prev), volume) < 0) break;
            
            while (fcmp(R, L) > 0) {
                M = (L+R) / 2;
                
                if (fcmp(volume, cal(total, M, prev)) > 0)
                    L = M;
                else
                    R = M;
            }
            
            ans.eb(M);
            prev = M;
        }
        
        cout << "Case " << c++ << ": " << fixed << setprecision(2) << cal(total, top, o_prev) << endl;
        if (ans.empty()) {
            cout << "insufficient volume\n";
        } else {
            for (int i = 0; i < ans.size(); i++)
                cout << fixed << setprecision(2) << ans[i]-o_prev << " \n"[i == ans.size()-1];
        }
    }
}