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

int _size;
vec<int> pset(5000);

void initSet(int n) {
    pset.resize(n);
    for (int i = 0; i < n; i++) pset[i] = i;
    _size = n;
}

int findSet(int i) {
    return (pset[i] == i ? i : pset[i] = findSet(pset[i]));
}

void unionSet(int i, int k) {
    if (findSet(i) != findSet(k)) {
        pset[findSet(i)] = findSet(k);
        
        _size--;
    }
}

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n;
        cin >> n;
        
        
        n *= 2;
        initSet(n);
        
        string str;
        
        cin >> str;
        
        vec<vec<int>> _list(n);
        
        int lev = 0;
        for (int i = 0; i < n; i++) {
            if (str[i] == '(') {
                // if (_list[lev].empty())
                _list[lev].eb(i);
                    
                lev++;
            } else {
                _list[lev].clear();
                lev--;
                
                if (_list[lev].size() == 1) {
                    unionSet(i, _list[lev].back());    
                } else {
                    unionSet(_list[lev].back(), _list[lev][_list[lev].size()-2]);
                    unionSet(_list [lev].back(), i);
                }
                
                // cout << i+1 << ' ' << k+1 << endl;
            }
        }
        
        cout << _size << endl;
    }
}