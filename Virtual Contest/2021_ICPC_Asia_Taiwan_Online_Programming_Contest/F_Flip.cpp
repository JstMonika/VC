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

struct Item {
    ll ans, lNum, rNum;
    bool left, right, f;
}; 

using ti = tuple<ll, ll, ll>;
struct SegTree {
    int n;
    deq<bool> _list;
    vec<Item> st;
    
    SegTree() {}
    SegTree(int n, deq<bool> _list) : n(n), _list(_list) {
        st.resize(4 * n);
        
        build(0, n-1, 1);
    }
    
    void pull(int idx, int l, int r) {
        // cout << l << ' ' << r << ": pull\n";
        
        st[idx].left = st[idx*2].left;
        st[idx].right = st[idx*2+1].right;
        
        int m = (l+r) / 2;
        st[idx].lNum = (st[idx*2].lNum == m-l+1 and st[idx*2].right != st[idx*2+1].left ? st[idx*2].lNum + st[idx*2+1].lNum : st[idx*2].lNum);
        st[idx].rNum = (st[idx*2+1].rNum == r-(m+1)+1 and st[idx*2].right != st[idx*2+1].left ? st[idx*2+1].rNum + st[idx*2].rNum : st[idx*2+1].rNum);
    
        st[idx].ans = st[idx*2].ans + st[idx*2+1].ans + (st[idx*2].right != st[idx*2+1].left ? st[idx*2].rNum * st[idx*2+1].lNum : 0);
    }
    
    void push(int idx) {
        if (st[idx].f) {
            // st[idx].left = !st[idx].left;
            // st[idx].right = !st[idx].right;
            
            st[idx*2].f = !st[idx*2].f;
            st[idx*2].left = !st[idx*2].left;
            st[idx*2].right = !st[idx*2].right;
            
            st[idx*2+1].f = !st[idx*2+1].f;
            st[idx*2+1].left = !st[idx*2+1].left;
            st[idx*2+1].right = !st[idx*2+1].right;
            
            st[idx].f = false;
        }
    }

    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx].ans = st[idx].lNum = st[idx].rNum = 1;
            st[idx].left = st[idx].right = _list[l];
            st[idx].f = false;
            
            // cout << l << ' ' << r << ": " << st[idx].ans << endl;
            return;
        }
        
        int m = (l+r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx, l, r);
        
        // cout << l << ' ' << r << ": " << st[idx].ans << endl;
    }
    
    void modify(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R) {
            // cout << l << ' ' << r << endl;
            st[idx].f = !st[idx].f;
            st[idx].left = !st[idx].left;
            st[idx].right = !st[idx].right;
            return;
        } else if (r < L or R < l) {
            return;
        }
        
        push(idx);
        
        int m = (l+r) / 2;
        modify(l, m, L, R, idx*2);
        modify(m+1, r, L, R, idx*2+1);
        
        pull(idx, l, r);
    }
    
    ti query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R) {
            return {st[idx].ans, st[idx].lNum, st[idx].rNum};
        } else if (r < L or R < l) {
            return {0, 0, 0};
        }
        
        push(idx);
    
        int m = (l+r) / 2;
        ti lItem = query(l, m, L, R, idx*2);
        ti rItem = query(m+1, r, L, R, idx*2+1);
        
        ti ret;
        get<0>(ret) = get<0>(lItem) + get<0>(rItem) + (st[idx*2].right != st[idx*2+1].left ? get<2>(lItem) * get<1>(rItem) : 0);
        get<1>(ret) = (get<1>(lItem) == m-l+1 and (st[idx*2].right != st[idx*2+1].left) ? get<1>(lItem) + get<1>(rItem) : get<1>(lItem));
        get<2>(ret) = (get<2>(rItem) == r-(m+1)+1 and (st[idx*2].right != st[idx*2+1].left) ? get<2>(rItem) + get<2>(lItem) : get<2>(rItem));
        
        return ret;
    }
};


int main()
{
    yccc;
    
    int n, q;
    cin >> n >> q;
    
    deq<bool> _list(n);
    for (auto &i : _list)
        cin >> i;
    
    SegTree st(n, _list);
    
    while (q--) {
        int t, l, r;
        cin >> t >> l >> r;
        
        if (t == 1) {
            st.modify(0, n-1, l-1, r-1, 1);
        } else {
            // cout << 0 << ' ' << n-1 << ' ' << l-1 << ' ' << r-1 << endl;
            cout << get<0>(st.query(0, n-1, l-1, r-1, 1)) << endl;
        }
    }
}   