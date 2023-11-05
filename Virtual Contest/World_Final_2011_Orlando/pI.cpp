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
    vec<int> st, tag;
    
    SegTree() {}
    SegTree(int n) : n(n) {
        st.resize(4*n);
        tag.resize(4*n);
    }
    
    void pull(int idx) {
        st[idx] = min(st[idx*2], st[idx*2+1]);
    }
    
    void push(int idx) {
        st[idx*2] += tag[idx];
        st[idx*2+1] += tag[idx];
        
        tag[idx*2] += tag[idx];
        tag[idx*2+1] += tag[idx];
        
        tag[idx] = 0;
    }
    
    void build(int l, int r, int idx) {
        if (l == r) {
            st[idx] = 0;
            return;
        }
        
        int m = (l+r) / 2;
        
        build(l, m, idx*2);
        build(m+1, r, idx*2+1);
        
        pull(idx);
    }
    
    void modify(int l, int r, int L, int R, int idx, int val) {
        if (L <= l and r <= R) {
            st[idx] += val;
            tag[idx] += val;
            return;
        } else if (r < L or R < l)
            return;
        
        int m = (l+r) / 2;
        
        push(idx);
        
        modify(l, m, L, R, idx*2, val);
        modify(m+1, r, L, R, idx*2+1, val);
        
        pull(idx);
    }
    
    //* 0 exists.
    bool query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R)
            return st[idx] == 0;
        else if (r < L or R < l)
            return 0;
        
        push(idx);
        
        int m = (l+r) / 2;
        
        return query(l, m, L, R, idx*2) or query(m+1, r, L, R, idx*2+1);
    }
};

struct EP {
    int type;
    int l, r;
    int p;
    
    EP() {}
    EP(int type, int l, int r, int p) : type(type), l(l), r(r), p(p) {}
    
    bool operator<(EP src) {
        if (src.p != p)
            return p < src.p;
            
        return type < src.type;
    }
};

bool solve(vec<p<int>> m, int r) {
    int n = 2000005, o = 1000001;
    SegTree st(n);
    
    vec<EP> _list;
    for (int i = 0; i < m.size(); i++) {
        _list.eb(1, m[i].S - r, m[i].S + r, m[i].F - r);
        _list.eb(4, m[i].S - r, m[i].S + r, m[i].F + r);
    }
    
    _list.eb(3, -r, r, -r);
    _list.eb(2, -r, r, r);
    
    sort(al(_list));
    // for (auto i : _list)
    //     cout << "Segment((" << i.p << ", " << i.l << "), (" << i.p << ", " << i.r << "))\n";
    // cout << "-\n";
    
    int prev = -INF;
    bool checking = false;
    for (auto i : _list) {
        // cout << i.p << ", " << i.type << ": ";
        // for (int k = -r; k <= r; k++)
        //     cout << st.query(0, n-1, k+o, k+o, 1);
        // cout << endl;
        // cout << "result: " << st.query(0, n-1, -r+o, r+o, 1) << endl;
        
        if (i.p != prev + 1 and checking)
            if (st.query(0, n-1, -r+o, r+o, 1))
                return true;
                
        switch (i.type) {
            case 1:
                // cout << "modify " << i.l << " to " << i.r << endl;
                st.modify(0, n-1, i.l+o, i.r+o, 1, 1);
                
                if (checking) {
                    // cout << i.p << ": ";
                    // for (int k = -r; k <= r; k++)
                    //     cout << st.query(0, n-1, k+o, k+o, 1);
                    // cout << endl;
                    
                    if (st.query(0, n-1, -r+o, r+o, 1))
                        return true;
                }

                break;
            case 4:
                // cout << "restore " << i.l << " to " << i.r << endl;
                if (checking) {
                    // cout << i.p << ": ";
                    // for (int k = -r; k <= r; k++)
                    //     cout << st.query(0, n-1, k+o, k+o, 1);
                    // cout << endl;
                    
                    if (st.query(0, n-1, -r+o, r+o, 1))
                        return true;
                }
                
                st.modify(0, n-1, i.l+o, i.r+o, 1, -1);
                break;
            case 2:
            case 3:
                if (st.query(0, n-1, -r+o, r+o, 1))
                    return true;
                    
                checking = !checking;
                break;
        }
        
        // cout << endl;
        
        prev = i.p;
    }
    
    return false;
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (n == -1) break;
        
        vec<p<int>> _list(n);
        for (auto &i : _list)
            cin >> i.F >> i.S;
            
        int L = 1, R = 1000001, ans;
        while (L <= R) {
            int M = (L+R) / 2;
            
            if (solve(_list, M)) {
                ans = M;
                L = M+1;
            } else {
                R = M-1;
            }
        }
        
        cout << "Case " << c++ << ": " << (ans >= 1000000 ? "never" : to_string(ans+1)) << endl;
    }
}