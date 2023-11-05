#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

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

int next(int i, int n) {
    return (i+n) % 4;
}

vec<p<int>> _list(4);
bool check(int i) {
    p<int> f = {_list[next(i, 1)].F - _list[i].F, _list[next(i, 1)].S - _list[i].S};
    p<int> s = {_list[next(i, 2)].F - _list[i].F, _list[next(i, 2)].S - _list[i].S};
    
    if (f.F * s.S - f.S * s.F <= 0) return false;
    return true;
}

int main()
{
    yccc;
    
    for (auto &i : _list)
        cin >> i.F >> i.S;
        
    for (int i = 0; i < 4; i++) {
        if (!check(i)) {
            cout << "No";
            return 0;
        }       
    }
    
    cout << "Yes";
}