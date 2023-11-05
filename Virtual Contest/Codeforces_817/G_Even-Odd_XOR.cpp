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
        
        deq<int> odd, even;
        
        int idx = 4, now;
        while (n >= 4) {
            if (n & idx) {
                now = idx / 2;
                for (int i = idx; i < idx * 2; i++) {
                    if (now-- > 0) odd.eb(i);
                    else even.eb(i);
                }
                
                n -= idx;
            }
            
            idx *= 2;
            // cout << n << endl;
        }
        
        if (n == 1) {
            odd.eb(0);
        } else if (n == 2) {
            odd.eb(0);
            even[0] |= (1 << 30);
            even.eb(1<<30);
        } else if (n == 3) {
            odd.eb(1);
            odd.eb(3);
            even.eb(2);
        }
        
        // debug(n);
        // devec(odd);
        // devec(even);
        
        int o = 0, e = 0;
        for (auto i : odd)
            o ^= i;
        for (auto i : even)
            e ^= i;
            
        // cout << o << ' ' << e << endl;
        
        cout << odd[0];
        
        idx = 1;
        while (idx-1 < even.size()) {
            cout << ' ' << even[idx-1];
            
            if (idx < odd.size())
                cout << ' ' << odd[idx];
            
            idx++;
        }
        
        cout << endl;
    }
}