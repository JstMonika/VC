#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// template<typename T> using p = pair<T, T>;
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

bool clamp(ll src, ll l, ll r) {
    return src >= l && src <= r;
}

ll a, m, p, q, r, s;
bool uCheck(ll base, ll ubound, ll times) {
    while (times--) {
        base *= m;
        
        if (base > ubound)
            return false;
    }
    
    if (base > ubound)
        return false;
        
    return true;
}

ll iPow(ll ta, ll tb) {
    ll ret = 1;
    do {
        if (tb & 1) ret *= ta;
        ta *= ta;
    } while (tb >>= 1);
    
    return ret;
}

ll sum(vec<pair<string, ll>> a, vec<pair<string, ll>> b) {
    ll sa = 0, sb = 0;
    
    for (auto i : a) {
        sa += i.S;
    }
    
    for (auto i : b) {
        sb += i.S;
    }
    
    return sa - sb;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> a >> m >> p >> q >> r >> s) {
        if (!a) break;
        
        if (clamp(p, r, s) and clamp(q, r, s)) {
            cout << "Case " << c++ << ": empty\n";
            continue;
        }
        
        if (m == 1) {
            if (p >= r) cout << "Case " << c++ << ": impossible\n";
            else if (q + (r-p+a-1)/a*a > s) cout << "Case " << c++ << ": impossible\n";
            else cout << "Case " << c++ << ": " << (r-p+a-1)/a << "A\n";
            
            continue;
        } else {
            vec<pair<string, ll>> vans, tmp;
            vans.eb("?", llINF);
            
            for (int i = 0; i <= 40; i++) {
                if (!uCheck(q, s, i)) {
                    break;
                }
                
                ll P = p * iPow(m, i), Q = q * iPow(m, i);
                
                vec<int> _list(i+1);
                if (Q-P > s-r) {
                    continue;
                } else if (!(clamp(P, r, s) and clamp(Q, r, s))) {
                    ll _min = min(r-P, s-Q), _max = max(r-P, s-Q);
                    for (int k = i; k >= 0; k--) {
                        _list[k] = (_min + (pow(m, k) * a) - 1) / (pow(m, k) * a);
                        
                        if (_list[k] * pow(m, k) * a <= _max) {
                            _min -= _list[k] * pow(m, k) * a;
                            _max -= _list[k] * pow(m, k) * a; 
                            break;
                        }
                        else {
                            _list[k]--;
                            _min -= _list[k] * pow(m, k) * a;
                            _max -= _list[k] * pow(m, k) * a;
                        }
                    }
                    
                    if (_min > 0) continue;
                }
                
                // devec(_list);
                
                tmp.clear();
                for (int k = i; k >= 0; k--) {
                    if (k == i and _list[k] == 0)
                        tmp.eb("M", 1);
                    else if (_list[k] == 0) {
                        if (k != 0)
                            tmp.back().S++;
                    }
                    else {
                        tmp.eb("A", _list[k]);
                        
                        if (k != 0)
                            tmp.eb("M", 1);
                    }
                }
                
                // devec(tmp);
                
                if (sum(tmp, vans) <= 0) {
                    int idx = 0;
                    
                    if (sum(tmp, vans) == 0) {
                        while (tmp[idx] == vans[idx]) idx++;
                    }
                    
                    if (sum(tmp, vans) < 0 or tmp[idx] < vans[idx]) {
                        vans = tmp;
                    }
                }
            }
            
            if (vans[0].S != llINF) {
                cout << "Case " << c++ << ":";
                for (auto k : vans)
                    cout << ' ' << k.S << k.F;
                cout << endl;
            }
            else 
                cout << "Case " << c++ << ": impossible" << endl;
        }
    }
}