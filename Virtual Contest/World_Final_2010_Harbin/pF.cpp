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

int same(int a, int b, int c) {
    if (a == b and b == c)
        return 2;
    if (a == b or b == c or c == a)
        return 1;
    return 0;
}

double cal(int a, int b, int c, int h) {
    
}

double tri(int b1, int b2, int top, int bottom, int h) {
    if (b1 == b2 and b2 == bottom)
        return 1;
        
    return 0.5;
}

int main()
{
    yccc;
    
    int s, p, d, h, c = 1, tmp;
    while (cin >> s >> p >> d >> h) {
        if (!s) break;
        
        vec<vec<int>> _list(s+2);
        for (int i = 0; i < s+2; i++) {
            if (i == 0 or i == s+1)
                _list[i] = vec<int>(p+5, -1);
            else {
                _list[i].eb(-1);
                
                for (int k = 0; k < (i%2 ? p : p+1); k++) {
                    cin >> tmp;
                    _list[i].eb(tmp);
                }
                
                _list[i].eb(-1);
            }
        }
        
        double ans = 0;
        for (int i = 1; i < s+1; i++) {
            for (int k = 1; k < _list[i].size()-2; k++) {
                if (i % 2) {
                    //* up: _list[i-1][k+1]
                    
                    switch (same(_list[i][k], _list[i][k+1], _list[i-1][k+1])) {
                        case 0:
                            ans += cal(_list[i][k], _list[i][k+1], _list[i-1][k+1], h);
                            break;
                        case 1:
                            ans += tri(_list[i][k], _list[i][k+1], _list[i-1][k+1], _list[i+1][k+1], h);
                            ans += tri(_list[i][k+1], _list[i-1][k+1], _list[i][k], _list[i-1][k+2], h);
                            ans += tri(_list[i-1][k+1], _list[i][k], _list[i][k+1], _list[i-1][k], h);
                            break;
                    }
                    
                    switch (same(_list[i][k], _list[i][k+1], _list[i+1][k+1])) {
                        case 0:
                            ans += cal(_list[i][k], _list[i][k+1], _list[i+1][k+1], h);
                            break;
                        case 1:
                            ans += tri(_list[i][k], _list[i][k+1], _list[i+1][k+1], _list[i-1][k+1], h);
                            ans += tri(_list[i][k+1], _list[i+1][k+1], _list[i][k], _list[i+1][k+2], h);
                            ans += tri(_list[i+1][k+1], _list[i][k], _list[i][k+1], _list[i+1][k], h);
                            break;
                    }
                } else {
                    //* up: _list[i-1][k]
                    
                    
                    switch (same(_list[i][k], _list[i][k+1], _list[i-1][k])) {
                        case 0:
                            ans += cal(_list[i][k], _list[i][k+1], _list[i-1][k]);
                            break;
                        case 1:
                            ans += tri(_list[i][k], _list[i][k+1], _list[i-1][k], _list[i+1][k]);
                            ans += tri(_list[i][k+1], _list[i-1][k], _list[i][k], _list[i-1][k+1]);
                            ans += tri(_list[i-1][k], _list[i][k], _list[i][k+1], _list[i-1][k-1]);
                            break;
                    }
                    
                    switch (same(_list[i][k], _list[i][k+1], _list[i+1][k])) {
                        case 0:
                            ans += cal(_list[i][k], _list[i][k+1], _list[i+1][k]);
                            break;
                        case 1:
                            ans += tri(_list[i][k], _list[i][k+1], _list[i+1][k], _list[i-1][k]);
                            ans += tri(_list[i][k+1], _list[i+1][k], _list[i][k], _list[i+1][k+1]);
                            ans += tri(_list[i+1][k], _list[i][k], _list[i][k+1], _list[i+1][k-1]);
                            break;
                    }
                }
            }
        }
        
        cout << "Case " << c++ << ": " << round(ans * d) << endl;
        devec2(_list);
    }
}