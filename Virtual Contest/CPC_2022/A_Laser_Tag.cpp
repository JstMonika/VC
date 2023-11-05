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

struct Node {
    int ans;
    int tag;
};

struct SegTree {
    int n;
    vec<Node> st;
    
    SegTree() {}
    SegTree(int n) : n(n) {
        st.resize(4*n);
        
        modify(0, n-1, 0, n-1, 1, 1);
    }
    
    void push(int idx, int l, int r) {
        if (st[idx].tag != -1) {
            int m = (l+r) / 2;
            
            st[idx*2].ans = st[idx].tag * (m-l+1);
            st[idx*2].tag = st[idx].tag;
            
            st[idx*2+1].ans = st[idx].tag * (r-(m+1)+1);
            st[idx*2+1].tag = st[idx].tag;
            
            st[idx].tag = -1;
        }
    }
    
    void pull(int idx) {
        st[idx].ans = st[idx*2].ans + st[idx*2+1].ans;
    }
    
    void modify(int l, int r, int L, int R, int idx, int val) {
        if (L <= l and r <= R) {
            st[idx].tag = val;
            
            if (val == 0) {
                st[idx].ans = 0;
            } else {
                st[idx].ans = r - l + 1;
            }
            
            return;
        } else if (r < L or R < l) {
            return;
        }
        
        push(idx, l, r);
        
        int m = (l+r) / 2;
        
        modify(l, m, L, R, idx*2, val);
        modify(m+1, r, L, R, idx*2+1, val);
        
        pull(idx);
    }
    
    int query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R) {
            return st[idx].ans;
        } else if (r < L or R < l) {
            return 0;
        }
        
        push(idx, l, r);
        
        int m = (l+r) / 2;
        
        return query(l, m, L, R, idx*2) + query(m+1, r, L, R, idx*2+1);
    }
};

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        int n, k;
        cin >> n >> k;
        
        SegTree st(n);
        
        // cout << "???\n";
        
        vec<pair<int, p<int>>> _list(k);
        for (auto &i : _list) 
            cin >> i.S.F >> i.S.S >> i.F;
        
        sort(al(_list));
        
        for (auto &i : _list) {
            int L = i.S.F-1, R = i.S.S-1;
            // debug(L);
            // debug(R);
            
            // cout << st.query(L, R, 0, n-1, 1) << endl;
            if (st.query(0, n-1, L, R, 1)) {
                st.modify(0, n-1, L, R, 1, 0);
                // cout << st.query(0, n-1, 0, n-1, 1) << endl;
                st.modify(0, n-1, L, L, 1, 1);
                // cout << st.query(0, n-1, 0, n-1, 1) << endl;
                st.modify(0, n-1, R, R, 1, 1);
                // cout << st.query(0, n-1, 0, n-1, 1) << endl;
            }
        }
        
        cout << st.query(0, n-1, 0, n-1, 1) << endl;
    }
}