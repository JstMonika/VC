#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
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

string str;
deque<bool> exist;
int m, n, rest;

struct SegTree {
    int num;
    vec<int> st;
    
    SegTree() {}
    
    void init(int src) {
        num = src;
        st.resize(4 * num);
        build(1, 0, num-1);
    }
    
    void build(int idx, int l, int r) {
        if (l == r) {
            st[idx] = 1;
            return;
        }
        
        int m = (l+r) / 2;
        build(idx*2, l, m);
        build(idx*2+1, m+1, r);
        
        pull(idx);
    }
    
    void pull(int idx) {
        st[idx] = st[idx*2] + st[idx*2+1];
    }
    
    void modify(int idx, int l, int r, int t) {
        if (l == r) {
            st[idx] = 0;
            return;
        }
        
        int m = (l+r) / 2;
        if (t <= m)
            modify(idx*2, l, m, t);
        else
            modify(idx*2+1, m+1, r, t);
        
        pull(idx);
    }
    
    int query(int idx, int l, int r, int L, int R) {
        if (r < L or R < l)
            return 0;
        if (L <= l and r <= R)
            return st[idx];
        
        int m = (l+r) / 2;
        return query(idx*2, l, m, L, R) + query(idx*2+1, m+1, r, L, R);
    }
    
    int find(int pos, int next) {
        int count = query(1, 0, num-1, 0, pos);
        
        int ans;
        if (rest - count >= next) { //* behind
            int l = pos+1, r = num-1, m;
            while (l <= r) {
                m = (l+r) / 2;
                int ret = query(1, 0, num-1, 0, m);
                
                if (ret < count + next)
                    l = m+1;
                else if (ret > count + next)
                    r = m-1;
                else {
                    ans = m;
                    r = m-1;
                }
            }
            
            //? m.
        } else { //* front
            int l = 0, r = pos-1, m;
            while (l <= r) {
                m = (l+r) / 2;
                int ret = query(1, 0, num-1, 0, m);
                
                if (ret < next - (rest - count))
                    l = m+1;
                else if (ret > next - (rest - count))
                    r = m-1;
                else {
                    ans = m;
                    r = m-1;
                }
            }
            
            //? m.
        }
        
        return ans;
    }
};

SegTree seg;

int find(int idx, int next) {
    int ret = seg.find(idx, next);
    cout << ret << endl;
    exist[ret] = true;
    rest--;
    seg.modify(1, 0, m-1, ret);
    return ret;
}

bool check(string goal, string src) {
    // cout << "here?" << endl;
    int g[26] = {0}, s[26] = {0};
    
    for (auto i : goal)
        g[i - 'A']++;
    for (auto i : src)
        s[i - 'A']++;
        
    for (int i = 0; i < 26; i++)
        if (g[i] * 2 > s[i])
            return false;
            
    return true;
}

int first(int next, char ch) {
    while (exist[next])
        (next += 1) %= m;
    
    if (str[next] != ch)
        return -1;
    
    exist[next] = true;
    rest--;
    seg.modify(1, 0, m-1, next);
    
    return next;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> str) {
        if (str == "X")
            break;
        
        m = str.size();
        seg.init(m);
        
        exist.resize(m);
        fill(al(exist), false);
        rest = m;
        
        set<string> ans;
        
        for (n = m/2; n >= 1; n--) {
            ans.clear();
            
            for (int s = 0; s < m; s++) {
                for (int i = 0; i < m; i++) {
                    fill(al(exist), false);
                    rest = m;
                    seg.init(m);
                    
                    int count = n, idx = s;
                    string goal(n, 0);
                    goal[0] = str[s];
                    
                    exist[s] = true;
                    rest--;
                    seg.modify(1, 0, m-1, s);
                    
                    for (int z = 1; z < n; z++) {
                        idx = find(idx, i+1);
                        goal[z] = str[idx];
                    }
                    
                    if (!check(goal, str)) {
                        continue;
                    }
                    
                    auto backup = exist;
                    auto segBackup = seg;
                    auto restBackup = rest;
                    
                    for (int t = 0; t < m; t++) {
                        exist = backup;
                        seg = segBackup;
                        rest = restBackup;
                        
                        //* modify it.
                        int idx = -1, r_idx;
                        if ((r_idx = idx = first(t, goal[0])) == -1) {
                            continue;
                        }
                        
                        auto first_done = exist;
                        auto first_seg = seg;
                        auto first_rest = rest;
                        
                        for (int j = 0; j < m; j++) {
                            //* restore exist initial.
                            exist = first_done;
                            seg = first_seg;
                            rest = first_rest;
                            
                            idx = r_idx;
                            
                            bool good = true;
                            for (int z = 1; z < n; z++) {
                                idx = find(idx, j+1);
                                
                                if (goal[z] != str[idx]) {
                                    good = false;
                                    break;
                                }
                            }
                            
                            if (good) {
                                //* push ans.
                                ans.emplace(goal);
                            }
                        }
                    }
                }
            }
            
            if (ans.size() == 1) {
                //* single answer.
                cout << "Code " << c++ << ": " << *ans.begin() << endl;
                break;
            } else if (ans.size() >= 2) {
                //* ambiguous.
                cout << "Code " << c++ << ": Codeword not unique\n"; 
                break;
            } 
        }
        
    }
}