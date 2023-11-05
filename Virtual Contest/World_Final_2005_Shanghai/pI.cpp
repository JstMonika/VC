#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
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
        if (!n) break;
        
        vec<pair<p<int>, int>> _list(n);
        for (auto &i : _list) {
            cin >> i.F.F >> i.F.S;
            i.S = 0;
        }
            
        
        int s;
        cin >> s;
        _list.resize(n+s);
        
        int h, m;
        for (int i = n; i < n+s; i++) {
            cin >> _list[i].F.F >> h;
            cin.get();
            cin >> m;
            
            _list[i].F.S = (h - 14) * 60 + m;
            _list[i].S = 1;
        }
        
        auto cmp = [](pair<p<int>, int> a, pair<p<int>, int> b) {
            if (a.F.S != b.F.S)
                return a.F.S < b.F.S;
            return a.S < b.S;
        };
        sort(al(_list), cmp);
        
        // devec(_list);
        
        int _s = _list.size();
        for (int i = 0; i < _s; i++) {
            if (_list[i].S) {
                int idx = -1, count = 0;
                
                for (int k = 0; k < i; k++) {
                    if (_list[k].S != 0) continue;
                    
                    if (_list[k].F.F > count and _list[k].F.F <= _list[i].F.F) {
                        count = _list[k].F.F;
                        idx = k;
                    }
                }
                
                if (idx != -1) {
                    _list[idx].S = 2;
                }
            }
        }
        
        int count = 0, ans = 0;
        for (int i = 0; i < _s; i++) {
            if (_list[i].S == 0) {
                count++;
                ans += _list[i].F.F;
            }
        }
        
        cout << "Trial " << c++ << ": " << count << ' ' << ans << endl;
    }
}