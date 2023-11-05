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

vec<ll> ans(200);

ll KMP(string S, string T) {
    string tmp = T + "@" + S;
    
    vec<int> count(tmp.size(), -1);
    
    int ret = 0;
    for (int i = 1; i < tmp.size(); i++) {
        int len = count[i-1];
        
        while (len != -1) {
            if (tmp[i] == tmp[len+1])
                break;
            else len = count[len];
        }
        
        if (tmp[i] == tmp[len+1]) count[i] = len + 1;
        else count[i] = -1;
            
        if (count[i]+1 == T.size()) ret++;
    }
    
    return ret;
}

int main()
{
    yccc;
    
    int n, c = 1;
    string p;
    while (cin >> n >> p) {
        vec<string> _list = {"0", "1"};
        
        while (_list.back().size() < p.size()) _list.eb(_list.back() + _list[_list.size()-2]);
        
        if (_list.size() > n) {
            cout << "Case " << c++ << ": " << KMP(_list[n], p) << endl;
        } else {    
            ans[_list.size()-1] = KMP(_list.back(), p);
            
            string pre_n = _list.back().substr(0, p.size()-1);
            string suf_n = _list.back().substr(_list.back().size() - p.size() + 1);
            
            _list.eb(_list.back() + _list[_list.size()-2]);
            ans[_list.size()-1] = KMP(_list.back(), p);
            
            string suf_n1 = _list.back().substr(_list.back().size() - p.size() + 1);
            
            ll one = KMP(suf_n1+pre_n, p), two = KMP(suf_n+pre_n, p), t = _list.size();
            while (t <= n) {
                ans[t] = ans[t-1] + ans[t-2] + one;
                swap(one, two);
                t++;
            }
            
            cout << "Case " << c++ << ": " << ans[n] << endl;
        }
    }
}