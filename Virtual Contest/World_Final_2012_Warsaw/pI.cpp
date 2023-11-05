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

#define LEFT 0
#define RIGHT 1
#define DOWN 2
#define UP 3

struct Line {
    int spx, spy, epx, epy;
    
    Line() {}
    Line(int spx, int spy, int epx, int epy) : spx(spx), spy(spy), epx(epx), epy(epy) {}
};

struct Event {
    int type, l, r, idx;
    
    Event() {}
    Event(int type, int l, int r, int idx) : type(type), l(l), r(r), idx(idx) {}
    
    bool operator<(Event a) const {
        if (idx != a.idx)
            return idx < a.idx;
        return type < a.type;
    }
};

struct SegTree {
    int _n;
    vec<int> st;
    
    SegTree() {}
    SegTree(int _n) : _n(_n) {
        st.resize(4*_n);
    }
    
    void pull(int idx) {
        st[idx] = st[idx*2] + st[idx*2+1];
    }
    
    void modify(int l, int r, int x, int idx, int val) {
        if (l == r) {
            st[idx] += val;
            return;
        }
        
        int m = (l+r) / 2;
        
        if (x <= m)
            modify(l, m, x, idx*2, val);
        else
            modify(m+1, r, x, idx*2+1, val);
            
        pull(idx);
    }
    
    int query(int l, int r, int L, int R, int idx) {
        if (L <= l and r <= R)
            return st[idx];
        else if (r < L or R < l)
            return 0;
        
        int m = (l+r) / 2;
        
        return query(l, m, L, R, idx*2) + query(m+1, r, L, R, idx*2+1);
    }
    
    int find(int l, int r, int L, int R, int idx) {
        if (r < L or R < l)
            return -1;
        if (l == r)
            return l;
        
        int m = (l+r) / 2;
        
        if (st[idx*2] != 0) {
            int lRet = find(l, m, L, R, idx*2);
            
            if (lRet != -1) return lRet;
        }
        
        return find(m+1, r, L, R, idx*2+1);
    }
};

ll ans, _n = 1000005;
p<int> pos;

void check(vec<Line> h, vec<Line> v) {
    vec<Event> _list;
    
    SegTree st(_n);
    
    for (auto i : h) {
        int s = min(i.spy,i.epy), t = max(i.spy,i.epy);
        _list.eb(1,i.spx,i.spx, s+1);
        _list.eb(3,i.spx,i.spx, t-1);
    }
    
    for (auto i : v) {
        int s = min(i.spx, i.epx), t = max(i.spx, i.epx);
        
        _list.eb(2, s+1, t-1, i.spy);
    }
    
    sort(al(_list));
    // for (auto i : _list)
    //     cout << i.type << ' ' << i.l << ' ' << i.r << ' ' << i.idx << endl;
    
    for (auto i : _list) {
        switch (i.type) {
            case 1: //* modify 1.
                st.modify(0, _n-1, i.l, 1, 1);
                break;
            case 2: { //* query
                
                int ret = st.query(0, _n-1, i.l, i.r, 1);
                
                if (ret) {
                    ans += ret;
                    pos = min(pos, {st.find(0, _n-1, i.l, i.r, 1), i.idx});
                    // cout << st.query(0, _n-1, 2, 2, 1);
                    // cout << st.query(0, _n-1, 3, 3, 1);
                    // cout << st.query(0, _n-1, 4, 4, 1);
                    // cout << endl;
                    // cout << "i.l, i.r: " << i.l << " " << i.r << " " << i.idx << endl;
                    // cout << "pos: " << pos.F << ' ' << pos.S << endl;
                }
                break;
            }
            case 3: //* modify -1.
                st.modify(0, _n-1, i.l, 1, -1);
        }
    }
}

int main()
{
    yccc;
    
    int R, C, m, n, c = 1;
    while (cin >> R >> C >> m >> n) {
        
        vec<vec<int>> row(R), column(C);
        map<p<int>, int> G;
        
        int x, y;
        for (int i = 0; i < m; i++) {
            cin >> x >> y;
            x--, y--;
            
            row[x].eb(y);
            column[y].eb(x);
            G[make_pair(x, y)] = 1;
        }
        for (int i = 0; i < n; i++) {
            cin >> x >> y;
            x--, y--;
            
            row[x].eb(y);
            column[y].eb(x);
            G[make_pair(x, y)] = 2;
        }
        
        for (auto &i : row)
            sort(al(i));
        for (auto &i : column)
            sort(al(i));
        
        vec<vec<Line>> h(2), v(2);
        
        bool same = false;
        for (int i = 0; i < 2; i++) {
            int pr, pc, nr, nc, dir;
            if (i)
                pr = R-1, pc = C, dir = LEFT;
            else
                pr = 0, pc = -1, dir = RIGHT;
                
            bool done = false;
            while (!done) {
                switch (dir) {
                    case UP: {
                        auto it = lower_bound(al(column[pc]), pr);
                        
                        if (it != column[pc].begin()) {
                            v[i].eb(pr, pc, *(--it), pc);
                            pr = *it;
                            dir = (G[make_pair(pr, pc)] == 1 ? RIGHT : LEFT);
                        } else {
                            v[i].eb(pr, pc, -1, pc);
                            done = true;
                        }
                        
                        break;
                    }
                    case DOWN: {
                        auto it = upper_bound(al(column[pc]), pr);
                        
                        if (it != column[pc].end()) {
                            v[i].eb(pr, pc, *it, pc);
                            pr = *it;
                            dir = (G[make_pair(pr, pc)] == 1 ? LEFT : RIGHT);
                        } else {
                            v[i].eb(pr, pc, R, pc);
                            done = true;
                        }
                        
                        break;
                    }
                    case LEFT: {
                        auto it = lower_bound(al(row[pr]), pc);
                        
                        if (it != row[pr].begin()) {
                            h[i].eb(pr, pc, pr, *(--it));
                            pc = *it;
                            dir = (G[make_pair(pr, pc)] == 1 ? DOWN : UP);
                        } else {
                            h[i].eb(pr, pc, pr, -1);
                            done = true;
                        }
                        
                        break;
                    }
                    case RIGHT: {
                        auto it = upper_bound(al(row[pr]), pc);
                        
                        if (it != row[pr].end()) {
                            h[i].eb(pr, pc, pr, *it);
                            pc = *it;
                            dir = (G[make_pair(pr, pc)] == 1 ? UP : DOWN);
                        } else {
                            h[i].eb(pr, pc, pr, C);
                            done = true;
                            
                            if (i == 0 and pr == R-1)
                                same = true;
                        }
                    }
                }
            }
        }
        
        // TODO.
        if (same)
            cout << "Case " << c++ << ": 0" << endl;
        else {
            pos = {INF, INF};
            ans = 0;
            
            check(h[0], v[1]);
            check(h[1], v[0]);
            
            if (ans == 0) {
                cout << "Case " << c++ << ": impossible" << endl;
            } else {
                cout << "Case " << c++ << ": " << ans;
                
                if (ans)
                    cout << ' ' << pos.F+1 << ' ' << pos.S+1 << endl;
                else
                    cout << endl;
            }
        }
    }
}