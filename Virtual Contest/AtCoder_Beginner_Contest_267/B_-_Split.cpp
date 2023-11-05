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
    
    string str;
    cin >> str;
    
    vec<int> _list(7);
    for (int i = 0; i < 10; i++) {
        if (str[i] == '1') {
            if (i == 0) _list[3]++;
            else if (i == 1) _list[2]++;
            else if (i == 2) _list[4]++;
            else if (i == 3) _list[1]++;
            else if (i == 4) _list[3]++;
            else if (i == 5) _list[5]++;
            else if (i == 6) _list[0]++;
            else if (i == 7) _list[2]++;
            else if (i == 8) _list[4]++;
            else if (i == 9) _list[6]++;
        }
    }
    
    for (int i = 1; i <= 6; i++) {
        if (_list[i] == 0) {
            bool L = false, R = false;
            for (int k = 0; k < i; k++) if (_list[k]) L = true;
            for (int k = i+1; k < 7; k++) if (_list[k]) R = true;
            
            if (L and R and str[0] == '0') {
                cout << "Yes";
                return 0;
            }
        }
    }
    
    cout << "No";
}