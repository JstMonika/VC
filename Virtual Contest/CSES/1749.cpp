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

struct SegTree {
    int n;
    vec<ll> st, val;
    
    void pull(int idx) {
        st[idx] = st[idx*2] + st[idx*2+1];
    }
    
    void query(int l, int r, int idx, int x) {
        if (l == r) {
            cout << val[l] << ' ';
            
            st[idx] = 0;
            return;
        }
        
        int m = (l+r) / 2;
        
        if (st[idx*2] >= x) {
            query(l, m, idx*2, x);
        } else {
            query(m+1, r, idx*2+1, x - st[idx*2]);
        }
        
        pull(idx);
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx] = 1;
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
    
    int n;
    cin >> n;
    
    vec<ll> _list(n);
    for (auto &i : _list)
        cin >> i;
        
    SegTree seg(n, _list);
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        
        seg.query(0, n-1, 1, tmp);
    }
}
