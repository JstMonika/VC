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

deq<ll> a, b, ta, tb;

bool takeover(int now) {
    if (now) {
        if (b[0] > a[0]) {
            a.pop_front();
            return true;
        } else return false;
    } else {
        if (a[0] > b[0]) {
            b.pop_front();
            return true;
        } else return false;
    }
}

bool merge(int now) {
    if (now) {
        if (b.size() >= 2) {
            ll tmp = b[0] + b[1];
            b.pop_front();
            b.pop_front();
            b.emplace_front(tmp);
            return true;
        } else return false;
    } else {
        if (a.size() >= 2) {
            ll tmp = a[0] + a[1];
            a.pop_front();
            a.pop_front();
            a.emplace_front(tmp);
            return true;
        } else return false;
    }
}

bool go(int i) {
    if (i) {
        if (!merge(0))
            return false;
    } else {
        if (!takeover(0))
            return false;
    }
    
    int now = 1;
    while (true) {
        if (a.size() == 0) return false;
        if (b.size() == 0) return true;
        
        if (takeover(now)) {
            
        } else {
            merge(now);
        }
        
        now = 1 - now;
    }
}

int main() {
    
    int n, m, c = 1;
    while (cin >> n >> m) {
        a.resize(n);
        b.resize(m);
        
        for (auto &i : a)
            cin >> i;
        for (auto &i : b)
            cin >> i;
           
        sort(al(a), greater<ll>());
        sort(al(b), greater<ll>());
         
        ta = a;
        tb = b;
        
        if (go(0)) {
            cout << "Case " << c++ << ": Takeover Incorporated\n";
            continue;
        }
        
        a = ta;
        b = tb;
        
        cout << "Case " << c++ << ": " << (go(1) ? "Takeover Incorporated" : "Buyout Limited") << endl;
    }
}