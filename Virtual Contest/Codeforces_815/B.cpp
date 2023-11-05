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

struct SegTree {
    int n;
    vec<ll> val;
    vec<p<ll>> st;
    vec<ll> ans;
    
    SegTree() {}
    SegTree(vec<ll> src) : val(src) {
        n = src.size();
        
        st.resize(4*n);
        ans.resize(4*n);
        build(0, n-1, 1);
    }
    
    void pull(int idx) {
        st[idx].F = max(st[idx*2].F, st[idx*2+1].F);
        st[idx].S = max(st[idx*2].S, st[idx*2+1].S);
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx].F = st[idx].S = val[l];
            return;
        }
        
        int m = (l+r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
    
        pull(idx);
    }
    
    p<ll> query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R) {
            return st[idx];
        } else if (r < L or R < l) {
            return {-INF, INF};
        }
        
        int m = (l+r) / 2;
        
        auto left = query(l, m, L, R, idx*2);
        auto right = query(m+1, r, L, R, idx*2+1);
        
        return {max(left.F, right.F), min(left.S, right.S)};
    }
};

int main()
{
    yccc;
    
    int n;
    cin >> n;
    while (n--) {
        int c;
        cin >> c;
        
        vec<ll> _list(c);
        for (auto &i : _list) cin >> i;
        
        SegTree st(_list);
        
        
    }
}