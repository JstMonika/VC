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

int find_size(vec<int> _list, int i) {
    int count = 0;
    
    for (int k = 0; k < _list.size(); ++k) {
        count += _list[k] * (1<<k & i ? 1 : 0);
    }
    
    return count;
}

vec<int> subset;
void find_subset(int i, int now, int val) {
    if (now == 0) subset.clear();
    
    if (now == 20) {
        if (val != 0 and val != i)
            subset.eb(val);
        return;
    }
    
    if (i & (1<<now))
        find_subset(i, now+1, val + (i & (1<<now)));
    find_subset(i, now+1, val);
}

int main()
{
    yccc;
    
    int R, C, n, c = 1;
    while (cin >> n >> R >> C) {
        if (!n) break;
        
        vec<int> _list(n);
        for (auto &i : _list) 
            cin >> i;
        
        deq<deq<bool>> dp(1<<n, deq<bool>(R+1));
        
        for (int i = 0; i < 1<<n; i++) {
            int _size = find_size(_list, i);
            find_subset(i, 0, 0);
            
            for (int k = 1; k <= _size; k++) {
                if (_size % k) continue;
                
                int h = _size / k;
                for (auto s : subset) {
                    if (find_size(_list, s) % k == 0)
                        dp[i][k] |= dp[s][k] and dp[i-s][k];
                    if (find_size(_list, s) % h == 0)
                        dp[i][k] |= dp[s][h] and dp[i-s][h];
                }
                
                dp[i][_size/k] = dp[i][k];
            }
        }
        
        if (dp[1<<n-1][min(R, C)])
            cout << "Case " << c++ << ": " << "Yes\n";
        else
            cout << "Case " << c++ << ": " << "No\n";
    }
}