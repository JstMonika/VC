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

struct Query {
    char ch;
    int a, b;
};

ostream& operator<<(ostream& out, Query src) {
    cout << src.ch << ' ' << src.a << ' ' << src.b << endl;
    return out;
}

struct SegTree {
    int n;
    vec<int> st, val;
    
    void pull(int idx) {
        st[idx] = st[idx*2] + st[idx*2+1];
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx] = val[l];
            return;
        }
        
        int m = (l+r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx);
    }
    
    void modify(int l, int r, int idx, int x, int v) {
        if (l == r) {
            st[idx] += v;
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
        if (L <= l and r <= R) return st[idx];
        if (r < L or R < l) return 0;
        
        int m = (l+r) / 2;
        return query(l, m, idx*2, L, R) + query(m+1, r, idx*2+1, L, R);
    }
    
    SegTree(int n, vec<int> src) : n(n), val(src) {
        st.resize(4*n);
        build(0, n-1, 1);
    }
};

int main()
{
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    vec<int> _list(n);
    for (auto &i : _list) {
        cin >> i;
    }
    
    auto value = _list;
    
    vec<Query> query(m);
    for (int i = 0; i < m; i++) {
        cin >> query[i].ch >> query[i].a >> query[i].b;
        
        if (query[i].ch == '?')
            value.eb(query[i].a);
        value.eb(query[i].b);
    }
    
    sort(al(value));
    value.resize(distance(value.begin(), unique(al(value))));
    
    vec<int> count(value.size());
    
    for (int i = 0; i < _list.size(); i++) {
        _list[i] = distance(value.begin(), lower_bound(al(value), _list[i]));
        count[_list[i]]++;
    }
    
    SegTree seg(value.size(), count);
    
    for (int i = 0; i < query.size(); i++) {
        if (query[i].ch == '?')
            query[i].a = distance(value.begin(), lower_bound(al(value), query[i].a));
        query[i].b = distance(value.begin(), lower_bound(al(value), query[i].b));
    
        if (query[i].ch == '?') {
            cout << seg.query(0, value.size()-1, 1, query[i].a, query[i].b) << endl;
        } else {
            seg.modify(0, value.size()-1, 1, _list[query[i].a-1], -1);
            seg.modify(0, value.size()-1, 1, query[i].b, 1);
            
            _list[query[i].a-1] = query[i].b;
        }
    }
}