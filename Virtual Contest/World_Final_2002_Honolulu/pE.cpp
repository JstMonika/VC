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

int _size;
vec<int> pset;

void initSet(int n) { 
    pset.resize(n);
    
    for (int i = 0; i < n; i++)
        pset[i] = i;
    
    _size = n;
}

int findSet(int i) {
    return pset[i] != i ? pset[i] = findSet(pset[i]) : i;
}

bool unionSet(int i, int k) {
    if (findSet(i) != findSet(k)) {
        pset[findSet(i)] = findSet(k);
        _size--;
        
        return true;
    }
    
    return false;
}

bool sizeSet() {
    return _size != 1;
}

struct Node {
    int x, y;
    int val;
    
    double dis(Node src) {
        int dx = x - src.x, dy = y - src.y;
        
        return sqrt(dx*dx + dy*dy);
    }
};

double ans;
vec<Node> _list;
vec<vec<pair<int, double>>> G;

void dfs(int now, int prev, double dis) {
    ans += _list[now].val * dis;
    
    for (int i = 0; i < G[now].size(); i++) {
        if (G[now][i].F != prev) {
            dfs(G[now][i].F, now, max(dis, G[now][i].S));
        }
    }
}

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        ans = 0;
        
        int total = 0;
        
        _list.clear();
        _list.resize(n);
        
        for (auto &i : _list) {
            cin >> i.x >> i.y >> i.val;
            total += i.val;
        }
            
        initSet(n);
            
        using p = pair<double, pii>;
        priority_queue<p, vec<p>, greater<p>> pq;
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < i; k++) {
                pq.emplace(_list[i].dis(_list[k]), make_pair(i, k));
            }
            
        G.clear();
        G.resize(n);
        
        while (sizeSet()) {
            auto now = pq.top();
            pq.pop();
            
            if (unionSet(now.S.F, now.S.S)) {
                G[now.S.F].eb(now.S.S, now.F);
                G[now.S.S].eb(now.S.F, now.F);
            }
        }
        
        dfs(0, -1, 0);
        
        cout << "Island Group: " << c++ << " Average " << fixed << setprecision(2) << ans / total << endl << endl;
    }
}