#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
template<typename T> using vec = vector<T>;

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

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

struct SegTree {
    int n;
    bool left;
    vec<int> st, src;
    
    SegTree(int n, vec<int> src, bool left) : n(n), src(src), left(left) {
        st.resize(4*n);
        
        build(0, n-1, 1);
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx] = left ? src[l] - l : src[l] + l;
            
            return;
        }
        
        int m = (l+r) / 2;
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx);
    }
    
    void pull(int idx) {
        st[idx] = min(st[idx*2], st[idx*2+1]);
    }
    
    void modify(int l, int r, int idx, int x, int v) {
        if (l == r) {
            st[idx] = left ? v - l : v + l;
            
            return;
        }
        
        int m = (l+r) / 2;
        if (x <= m)
            modify(l, m, idx*2, x, v);
        else
            modify(m+1, r, idx*2+1, x, v);
            
        pull(idx);
    }
    
    int query(int l, int r, int idx, int L, int R) {
        if (L <= l and r <= R)
            return st[idx];
            
        if (r < L or R < l)
            return INF;
            
        int m = (l+r) / 2;
        
        return min(query(l, m, idx*2, L, R), query(m+1, r, idx*2+1, L, R));
    }
};

int main()
{
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    vec<int> _list(n);
    for (auto &i : _list)
        cin >> i;
        
    SegTree segL(n, _list, true), segR(n, _list, false);    
    
    for (int i = 0; i < m; i++) {
        int q;
        cin >> q;
        
        if (q == 1) {
            int x, v;
            cin >> x >> v;
            
            segL.modify(0, n-1, 1, x-1, v);
            segR.modify(0, n-1, 1, x-1, v);
            
            _list[x-1] = v;
        } else {
            int tmp;
            cin >> tmp;
            
            cout << min(segL.query(0, n-1, 1, 0, tmp-1) + tmp-1, 
                        segR.query(0, n-1, 1, tmp-1, n-1) - tmp+1) << endl;
        }
    }
}