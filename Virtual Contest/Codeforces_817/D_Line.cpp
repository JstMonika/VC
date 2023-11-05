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
    
    int c;
    cin >> c;
    
    while (c--) {
        int n;
        cin >> n;
        
        string str;
        cin >> str;
        
        ll ans = 0;
        int _max = 0;
        vec<int> count(1000000);
        for (int i = 0; i < n/2; i++) {
            // cout << n-i-1-i << ' ';
            if (str[i] == 'L') count[n-i-1-i]++;
            _max = max(n-i-1-i, _max);
            
            ans += (str[i] == 'L' ? i : n-i-1);
        }
        for (int i = n/2; i < n; i++) {
            if (str[i] == 'R') count[i-(n-i-1)]++;
            _max = max(i-(n-i-1), _max);
            
            ans += (str[i] == 'L' ? i : n-i-1);
        }
        
        // for (int i = 0; i < n; i++) {
        //     cout << count[i] << ' ';
        // }
        // cout << endl;
        
        int idx = _max;
        for (int i = 0; i < n; i++) {
            while(idx >= 0 and count[idx] == 0) idx--;
            
            if (idx >= 0) {
                ans += idx;
                count[idx]--;
            }
            
            cout << ans << " \n"[i == n-1];
        }
    }
}