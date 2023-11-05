#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll mPOW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll nPOW(ll a, ll b) { ll res=1; do { if(b%2) res*=a; a*=a; } while (b>>=1); return res; }
ll mFAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
ll nFAC(ll a) { ll res = 1; REP1(i, a) res*=i; return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

deque<bool> _list;

struct node {
    bool l;
    bool r;
    int l_len;
    int r_len;
    int len;
    
    int val;
    bool lTag;
};

vector<node> seg;

#define IL(idx) idx*2
#define IR(idx) idx*2+1

bool check(int idx) {
    return (seg[IL(idx)].r != seg[IR(idx)].l);
}

void pull(int idx) { 
    seg[idx].val = seg[IL(idx)].val + seg[IR(idx)].val + (check(idx) ? seg[IL(idx)].r_len * seg[IR(idx)].l_len : 0); 
}

void push(int idx) {
    seg[IL(idx)].l ^= 1;
    seg[IL(idx)].r ^= 1;
    seg[IL(idx)].lTag ^= 1;
    
    seg[IR(idx)].l ^= 1;
    seg[IR(idx)].r ^= 1;
    seg[IR(idx)].lTag ^= 1;
}

void build(int l, int r, int idx) {
    cout << l << ' ' << r << ' ' << idx << endl;
    int M = (l+r)>>1;
    
    if (l == r) {
        seg[idx].l = seg[idx].r = _list[l];
        seg[idx].l_len = seg[idx].r_len = 1;
        seg[idx].len = 1;
        
        seg[idx].val = 1;
        seg[idx].lTag = false;
        
        return;
    }
    
    build(l, M, idx*2);
    build(M+1, r, idx*2+1);
    
    seg[idx].l = seg[IL(idx)].l;
    seg[idx].r = seg[IR(idx)].r;
    
    if (seg[IL(idx)].l_len == seg[IL(idx)].len)
        seg[idx].l_len = seg[IL(idx)].l_len + (check(idx) ? seg[IR(idx)].l_len : 0);
    else
        seg[idx].l_len = seg[IL(idx)].l_len;
        
    if (seg[IR(idx)].l_len == seg[IR(idx)].len)
        seg[idx].r_len = seg[IR(idx)].l_len + (check(idx) ? seg[IL(idx)].r_len : 0);
    else
        seg[idx].r_len = seg[IR(idx)].r_len;
    
    pull(idx);
    
    seg[idx].lTag = false;
}

int query(int ql, int qr, int l, int r, int idx) {
    
    // cout << ql << ' ' << qr << ' ' << l << ' ' << r << ' ' << idx << endl;
    
    if (r < ql or l > qr)
        return 0;
    if (ql <= l and qr >= r)
        return seg[idx].val;
        
    if (seg[idx].lTag)  {
        push(idx);
        seg[idx].lTag = false;
    }
    
    int M = (l+r)>>1;
    
    int ret = 0;
    
    if (ql <= M and qr >= M+1)
        ret = (check(idx) ? seg[IL(idx)].r_len * seg[IR(idx)].l_len : 0);
    
    int left = query(ql, qr, l, M, IL(idx));
    int right = query(ql, qr, M+1, r, IR(idx));
    
    // cout << (check(idx) ? "true" : "false") << endl;
    // cout << "[l, r] -> " << l << ' ' << r << ' ' << idx << endl;
    // cout << left << ' ' << right << ' ' << ret << endl << endl;
    
    return left + right + ret;
}

void modify(int ml, int mr, int l, int r, int idx) {
    if (r < ml or l > mr)
        return;
    if (ml <= l and mr >= r) {
        seg[idx].l ^= 1;
        seg[idx].r ^= 1;
        seg[idx].lTag ^= 1;
        
        return;
    }
        
    int M = (l+r)>>1;
    modify(ml, mr, l, M, IL(idx));
    modify(ml, mr, M+1, r, IR(idx));
    
    seg[idx].l = seg[IL(idx)].l;
    seg[idx].r = seg[IR(idx)].r;
    
    if (seg[IL(idx)].l_len == seg[IL(idx)].len)
        seg[idx].l_len = seg[IL(idx)].l_len + (check(idx) ? seg[IR(idx)].l_len : 0);
    else
        seg[idx].l_len = seg[IL(idx)].l_len;
        
    if (seg[IR(idx)].l_len == seg[IR(idx)].len)
        seg[idx].r_len = seg[IR(idx)].l_len + (check(idx) ? seg[IL(idx)].r_len : 0);
    else
        seg[idx].r_len = seg[IR(idx)].r_len;
    
    pull(idx);
    
    cout << (check(idx) ? "true" : "false") << endl;
    cout << l << ' ' << r << ' ' << idx << ' ' << seg[idx].val << endl;
}

int main()
{
    yccc;
    
    int n, k;
    cin >> n >> k;
    
    _list.resize(n);
    seg.resize(4 * n);
    
    for (auto &i : _list)
        cin >> i;
        
    build(0, n-1, 1);
    
    for (int i = 0; i < k; i++) {
        int a, l, r;
        cin >> a >> l >> r;
        // cout << endl << "-----------------" << endl;
        if (a == 1)
            modify(l-1, r-1, 0, n-1, 1);
        else
            cout << query(l-1, r-1, 0, n-1, 1) << endl;
            
        for (int k = 1; k <= 80; k++)
            cout << seg[k].val << ' ';
        cout << endl;
    }
}