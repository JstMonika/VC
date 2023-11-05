#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int gt = 0;

struct Node {
    ll val;
    ll addTag;
    ll assTag;
    ll t;
    
    Node() {
        val = addTag = assTag = t = 0;
    }
};

struct SegTree {
    int n;
    vec<Node> st;
    
    SegTree(int n) : n(n) {
        st.resize(4 * n);
        
        build(1, 0, n-1);
    }
    
    void build(int idx, int l, int r) {
        if (l == r) {
            st[idx].val = 0;
            return;
        }
        
        int m = (l + r) / 2;
        build(idx*2, l, m);
        build(idx*2+1, m+1, r);
    } 
    
    void modify(int idx, int l, int r, int L, int R, bool assign, int val) {
        // cout << l << ' ' << r << ' ' << L << ' ' << R << endl;
        // cout << flush;
        if (r < L or R < l)
            return;
        if (L <= l and r <= R) {
            if (assign) {
                st[idx].addTag = 0;
                st[idx].assTag = val;
            } else {
                st[idx].addTag += val;
            }
            
            st[idx].t = gt;
            cout << "gt: " << st[idx].t << endl;
            
            return;
        }
        
        push(idx);
        
        int m = (l+r) / 2;
        
        modify(idx*2, l, m, L, R, assign, val);
        modify(idx*2+1, m+1, r, L, R, assign, val);
    }
    
    void push(int idx) {
        if (st[idx].addTag) {
            st[idx*2].addTag += st[idx].addTag;
            st[idx*2].t = st[idx].t;
            st[idx*2+1].addTag += st[idx].addTag;
            st[idx*2+1].t = st[idx].t;
            
            st[idx].addTag = 0;
        } else {
            st[idx*2].assTag = st[idx].assTag;
            st[idx*2].t = st[idx].t;
            st[idx*2+1].assTag = st[idx].assTag;
            st[idx*2+1].t = st[idx].t;
            
            st[idx].assTag = 0;
        }
    }
    
    pii query(int idx, int l, int r, int L, int R, bool assign) {
        if (L <= l and r <= R) {
            st[idx].val += st[idx].addTag;
            st[idx].addTag = 0;
            
            return make_pair(st[idx].val, st[idx].t);
        }
        
        push(idx);
        
        int m = (l+r) / 2;
        
        if (L <= m) {
            return query(idx*2, l, m, L, R, assign);
        } else {
            return query(idx*2+1, m+1, r, L, R, assign);
        }
    }
};

int main()
{
    yccc;
    
    int n, m, q;
    cin >> n >> m >> q;
    
    SegTree col(m), row(n);
    
    for (gt = 0; gt < q; gt++) {
        int tmp;
        cin >> tmp;
        
        if (tmp == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            
            col.modify(1, 0, n-1, l-1, r-1, false, x);
        } else if (tmp == 2) {
            int l, x;
            cin >> l >> x;
            
            row.modify(1, 0, n-1, l-1, l-1, true, x);
        } else {
            int r, c;
            cin >> r >> c;
            
            auto pr = row.query(1, 0, n-1, r-1, r-1, true);
            auto pc = col.query(1, 0, n-1, c-1, c-1, false);
            
            cout << pr << ", " << pc << endl;
            
            if (pr.S > pc.S) {
                cout << pr.F << endl;
            } else {
                cout << pr.F + pc.F << endl;
            }
        }
    }
}