#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 0x3f3f3f3f;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

struct Node {
    ll l, r;
    p<ll> ans;
    ll ass, add;
    bool isAss, isAdd;
};

struct SegTree {
    int n;
    vec<int> _list;
    vec<Node> st;
    
    SegTree() {}
    SegTree(vec<int> _list) : _list(_list), n(_list.size()) {
        st.resize(4 * n);
        build(0, n-1, 1);
    }
    
    void build(int l, int r, int idx) {
        st[idx].l = l, st[idx].r = r;
        
        if (l == r) {
            st[idx].ans = make_pair(l * _list[l], _list[l]);
            st[idx].ass = st[idx].add = 0;
            return;
        }
        
        int m = (l + r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx);
    }
    
    void pull(int idx) {
        st[idx].ans = make_pair(st[idx*2].ans.F + st[idx*2+1].ans.F, st[idx*2].ans.S + st[idx*2+1].ans.S);
    }
    
    void push(int idx) {
        for (int i = idx*2; i <= idx*2+1; i++) {
            if (st[idx].isAss) {
                st[i].isAss = true;
                st[i].ass = st[idx].ass;
                st[i].add = 0;
                
                st[i].ans.F = ((st[i].r + st[i].l) * (st[i].r - st[i].l + 1) / 2) * st[i].ass;
                st[i].ans.S = (st[i].r - st[i].l + 1) * st[i].ass;
            }
            
            if (st[idx].isAdd) {
                st[i].isAdd = true;
                st[i].add += st[idx].add;
                
                
                st[i].ans.F += ((st[i].r + st[i].l) * (st[i].r - st[i].l + 1) / 2) * st[idx].add;
                st[i].ans.S += (st[i].r - st[i].l + 1) * st[idx].add;
            }
        }
        
        st[idx].isAss = false;
        st[idx].isAdd = false;
        st[idx].ass = 0;
        st[idx].add = 0;
    }
    
    void increase(int l, int r, int L, int R, int idx, int val) {
        if (L <= l and r <= R) {
            st[idx].isAdd = true;
            st[idx].add += val;
            
            st[idx].ans.F += ((st[idx].r + st[idx].l) * (st[idx].r - st[idx].l + 1) / 2) * val;
            st[idx].ans.S += (st[idx].r - st[idx].l + 1) * val;
            return;
        } else if (r < L or R < l) return;
        
        push(idx);
        
        int m = (l + r) / 2;
        
        increase(l, m, L, R, idx*2, val);
        increase(m+1, r, L, R, idx*2+1, val);
        
        pull(idx);
    }
    
    void assign(int l, int r, int L, int R, int idx, int val) {
        if (L <= l and r <= R) {
            st[idx].isAss = true;
            st[idx].ass = val;
            st[idx].isAdd = false;
            st[idx].add = 0;
            
            st[idx].ans.F = ((st[idx].r + st[idx].l) * (st[idx].r - st[idx].l + 1) / 2) * val;
            st[idx].ans.S = (st[idx].r - st[idx].l + 1) * val;
            return;
        } else if (r < L or R < l) return;
        
        push(idx);
        
        int m = (l + r) / 2;
        
        assign(l, m, L, R, idx*2, val);
        assign(m+1, r, L, R, idx*2+1, val);
        
        pull(idx);
    }
    
    p<ll> query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R) {
            return st[idx].ans;
        } else if (r < L or R < l) return p<ll>(0, 0);
        
        push(idx);
        
        int m = (l + r) / 2;
        
        auto left = query(l, m, L, R, idx*2);
        auto right = query(m+1, r, L, R, idx*2+1);
        
        return make_pair(left.F + right.F, left.S + right.S);
    }
};

int main()
{
    yccc;
    
    int n, q;
    cin >> n >> q;
    
    vec<int> _list(n);
    for (auto &i : _list)
        cin >> i;
    
    SegTree seg(_list);   
    while (q--) {
        int type;
        cin >> type;
        
        if (type == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            
            l--, r--;
            
            seg.increase(0, n-1, l, r, 1, x);
        } else if (type == 2) {
            int l, r, x;
            cin >> l >> r >> x;
            
            l--, r--;
            
            seg.assign(0, n-1, l, r, 1, x);
        } else {
            int l, r;
            cin >> l >> r;
            
            l--, r--;
            
            auto ret = seg.query(0, n-1, l, r, 1);
            
            if (ret.S == 0) {
                cout << (ret.F == 0 ? "Yes\n" : "No\n");
            } else if (ret.F % ret.S == 0) {
                int k = ret.F / ret.S;
                
                if (k >= l and k <= r) cout << "Yes\n";
                else cout << "No\n";
            } else cout << "No\n";
        }
    }
}