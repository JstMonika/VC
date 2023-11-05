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

bool clamp(double src, double min, double max) {
    return fcmp(src, min) >= 0 and fcmp(max, src) >= 0;
}

int decode(vec<int> src, int now) {
    if (now+4 >= src.size())
        return -1;
        
    int type = 0, base = 16;
    
    for (int i = 0; i < 5; i++) {
        type += base * src[now+i];
        base /= 2;
    }
    
    switch (type) {
        case 1:
            return 0;
        case 17:
            return 1;
        case 9:
            return 2;
        case 24:
            return 3;
        case 5:
            return 4;
        case 20:
            return 5;
        case 12:
            return 6;
        case 3:
            return 7;
        case 18:
            return 8;
        case 16:
            return 9;
        case 4:
            return 10;
        case 6:
            return 11;
    }
    
    return -1;
}

string translate(vec<int> _list) {
    if (decode(_list, 0) != 11) {
        reverse(al(_list));
        if (decode(_list, 0) != 11)
            return "bad code";
    }
    
    vec<int> ret;
    for (int i = 0; i < _list.size(); i += 6) {
        ret.eb(decode(_list, i));
        
        if (ret.back() == -1)
            return "bad code";
        if (i+5 < _list.size() and _list[i+5] == 1)
            return "bad code";
    }
    
    if (ret.back() != 11)
        return "bad code";
    
    int c = 0, k = 0, n = ret.size() - 4;
    for (int i = 1; i < ret.size()-3; i++) {
        if (ret[i] == 11)
            return "bad code";
        
        c += (((n - i) % 10) + 1) * ret[i];
        k += (((n - i + 1) % 9) + 1) * ret[i];
    }
    
    c %= 11;
    (k += c) %= 11;
    
    if (c != ret[ret.size()-3])
        return "bad C";
    else if (k != ret[ret.size()-2])
        return "bad K";
    
    string str(n, 0);
    for (int i = 1; i < ret.size()-3; i++) {
        str[i-1] = (ret[i] == 10 ? '-' : ret[i] + '0');
    }
    
    return str;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        vec<int> _list(n);
        for (auto &i : _list)
            cin >> i;
        
        int n_min, n_max, w_min, w_max;
        n_min = w_min = INF;
        n_max = w_max = 0;
        
        vec<int> narrow, wide;
        for (auto i : _list) {
            // cout << i << ' ' << _list[0]/1.1 << ' ' << _list[0]/0.9 << endl;
            if (clamp(i, _list[0] / 1.05 * 0.95, _list[0] / 0.95 * 1.05)) {
                narrow.eb(i);
                n_min = min(n_min, i);
                n_max = max(n_max, i);
            } else if (fcmp(_list[0]/1.05*0.95, i) > 0) {
                narrow.clear();
                break;
            }
            else {
                wide.eb(i);
                w_min = min(w_min, i);
                w_max = max(w_max, i);
            }
        }
        
        p<double> wr(w_max / 1.05, w_min / 0.95), nr(n_max / 1.05, n_min / 0.95);
        // debug(nr);
        // debug(wr);
        
        if (narrow.empty() or wide.empty() or fcmp(wr.F, wr.S) > 0 or fcmp(nr.F, nr.S) > 0)
            cout << "Case " << c++ << ": bad code\n";
        else if (fcmp(wr.F/2, nr.S) >= 0 or fcmp(nr.F, wr.S/2) >= 0)
            cout << "Case " << c++ << ": bad code\n";
        else {
            double base;
            if (clamp(nr.F, wr.F/2, wr.S/2))
                base = nr.F;
            else if (clamp(nr.S, wr.S/2, wr.F/2))
                base = nr.S;
            else
                base = wr.F/2;
            
            // cout << base << endl;
            // cout << nr.F << ' ' << nr.S << endl;
            // cout << nr.F/1.1 << ' ' << nr.F/0.9 << endl;
            // debug(nr);
            // debug(wr);
            int tmp = _list[0];
            for (auto &i : _list) {
                if (clamp(i, base*0.95, base*1.05))
                    i = 0;
                else 
                    i = 1;
            }
            // devec(_list);
            cout << "Case " << c++ << ": " << translate(_list) << endl;
        }
    }
}