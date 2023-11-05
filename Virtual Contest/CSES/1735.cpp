#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
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

struct Node {
    ll ans, addTag, assTag;
};

struct SegTree {
    int n;
    
    vec<Node> st;
    vec<ll> val;
    
    void pull(int idx) { //* push first?
        st[idx].ans = st[idx*2].ans + st[idx*2+1].ans;
    }
    
    void push(int l, int r, int idx) {        
        int m = (l+r) / 2;
        
        if (st[idx].assTag == 0) {
            st[idx*2].addTag += st[idx].addTag;
            st[idx*2].ans += st[idx].addTag * (m-l+1);
            
            st[idx*2+1].addTag += st[idx].addTag;
            st[idx*2+1].ans += st[idx].addTag * (r-m);
        } else {
            st[idx*2].addTag = st[idx].addTag;
            st[idx*2].assTag = st[idx].assTag;
            st[idx*2].ans = (st[idx].assTag + st[idx].addTag) * (m-l+1);
            
            st[idx*2+1].addTag = st[idx].addTag;
            st[idx*2+1].assTag = st[idx].assTag;
            st[idx*2+1].ans = (st[idx].assTag + st[idx].addTag) * (r-m);
        }
        
        st[idx].addTag = st[idx].assTag = 0;
    }   
    
    ll query(int l, int r, int idx, int L, int R) {
        if (l >= L and r <= R) return st[idx].ans;
        
        if (r < L or l > R) return 0;
        
        push(l, r, idx);
        
        int m = (l+r) / 2;
        
        return query(l, m, idx*2, L, R) + query(m+1, r, idx*2+1, L, R);
    }
    
    void modify(int l, int r, int idx, int L, int R, ll x, string str) {
        if (l >= L and r <= R) {
            if (str == "add") {
                st[idx].addTag += x;
                st[idx].ans += x * (r-l+1);
            } else {
                st[idx].addTag = 0;
                st[idx].assTag = x;
                st[idx].ans = x * (r-l+1);
            }
            
            return;
        }
        
        if (r < L or l > R) return;
        
        push(l, r, idx);
        
        int m = (l+r) / 2;
        modify(l, m, idx*2, L, R, x, str);
        modify(m+1, r, idx*2+1, L, R, x, str);
        
        pull(idx);
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx].ans = val[l];
            return;
        }
        
        int m = (l+r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx);
    }
    
    SegTree(int n, vec<ll> src) : n(n), val(src) {
        st.resize(4*n);
        build(0, n-1, 1);
    }
};

int main()
{
    yccc;
    
    int n, q;
    cin >> n >> q;
    
    vec<ll> _list(n);
    for (auto &i : _list)
        cin >> i;
        
    SegTree seg(n, _list);
    
    for (int i = 0; i < q; i++) {
        int m, a, b, x;
        cin >> m >> a >> b;
        
        if (m != 3)
            cin >> x;
        
        switch (m) {
            case 1:
                seg.modify(0, n-1, 1, a-1, b-1, x, "add");
                break;
            case 2:
                seg.modify(0, n-1, 1, a-1, b-1, x, "assign");
                break;
            case 3:
                cout << seg.query(0, n-1, 1, a-1, b-1) << endl;
                break;
        }
    }
}