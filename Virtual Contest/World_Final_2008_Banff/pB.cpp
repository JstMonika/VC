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

int MOD;

ll power(ll a, ll n) {
    ll src = 1;
    do {
        if (n % 2) (src *= a) %= MOD;
        (a *= a) %= MOD;
    } while (n >>= 1);
    
    return src;
}

int fstoi(string str) {
    if (str == "+") return 1;
    if (str == "-") return -1;
    
    return (str.size() == 0 ? 1 : stoi(str));
}

int main()
{
    yccc;
    
    string str;
    int c = 1;
    
    regex poly("(([+-]?[0-9]+|[+-])(n(\\^([0-9]+))?))|([+-]?[0-9]+|[+-])|(n(\\^([0-9]+))?)");
    while (cin >> str) {
        if (str == ".") break;
        
        vec<string> _list;
        auto it = sregex_iterator(al(str), poly);
        
        for (; it != sregex_iterator(); it++)
            _list.eb(it->str());
        
        debug(_list.back());
        MOD = fstoi(_list.back());
        
        bool good = true;
        
        int high;
        if (_list[0].find('^') != string::npos)
            high = fstoi(_list[0].substr(_list[0].find('^')+1));
        else high = (_list[0].find('n') != string::npos) ? 1 : 0;
            
        vec<p<ll>> poly;
        for (int i = 0; i < _list.size()-1; i++) {
            int coeff = fstoi(_list[i].substr(0, _list[i].find('n')));
            int power;
            if (_list[i].find('^') != string::npos)
                power = fstoi(_list[i].substr(_list[i].find('^')+1));
            else power = (_list[i].find('n') != string::npos) ? 1 : 0;
            
            poly.eb(coeff, power);
        }
        devec(poly);
        for (int i = 1; i <= high + 1; i++) {
            int m = 0;
            for (auto k : poly) {    
                // cout << k.S << ' ' << power(i, k.S) << endl;
                (m += (k.F * power(i, k.S) % MOD)) %= MOD;
                // cout << m << endl;
            }
            
            if (m) {
                good = false;
                break;
            }
        }
        
        cout << "Case " << c++ << ": " << (good ? "Always an integer\n" : "Not always an integer\n");
    }
    
}