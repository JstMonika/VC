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

vec<int> pset(1000);
void initSet(int i) { pset.resize(i); for (int k = 0; k < i; k++) pset[k] = k; }
int findSet(int i) { return (pset[i] == i ? i : pset[i] = findSet(pset[i])); }
void unionSet(int i, int k) { pset[findSet(i)] = findSet(k); }
bool isSameSet(int i, int k) { return findSet(i) == findSet(k); }

vec<vec<char>> _map;
vec<vec<int>> idx;

int r, c;
void go(int i, int k, int count) {
    idx[i][k] = count;
    
    for (int fi = -1; fi <= 1; fi++) {
        for (int fk = -1; fk <= 1; fk++) {
            if (i+fi >= 0 and i+fi < r and k+fk >= 0 and k+fk < c) {
                if (_map[i+fi][k+fk] == '#' and idx[i+fi][k+fk] == -1) {
                    go(i+fi, k+fk, count);
                }
            }
        }
    }
}

int main()
{
    yccc;
    
    int n = 1;
    while (cin >> r >> c) {
        if (r == 0) break;
        
        _map.clear();
        idx.clear();
        
        _map.resize(r);
        idx.resize(r);
        
        for (int i = 0; i < r; i++) {
            _map[i].resize(c, -1);
            idx[i].resize(c, -1);
            
            string tmp;
            cin >> tmp;
            
            for (int k = 0; k < c; k++)
                _map[i][k] = tmp[k];
        }
        
        int count = 0;
        for (int i = 0; i < r; i++) {
            for (int k = 0; k < c; k++) {
                if (_map[i][k] == '#' and idx[i][k] == -1) {
                    go(i, k, count++);
                }
            }
        }
        
        vec<vec<int>> adj(count, vec<int>(count, INF));
        
        int len;
        for (int i = 0; i <= r; i++) {
            int prev = -1, now = -1;
            
            len = 0;
            for (int k = 0; k < c; k++) {
                bool _find = false;
                if (i == r) {
                    if (idx[i-1][k] != -1) {
                        now = idx[i-1][k];
                        _find = true;
                    }
                } else if (i) {
                    if (idx[i-1][k] != -1 or idx[i][k] != -1) {
                        now = (idx[i][k] != -1 ? idx[i][k] : idx[i-1][k]);
                        _find = true;
                    }
                } else {
                    if (idx[i][k] != -1) {
                        now = idx[i][k];
                        _find = true;
                    }
                }
                
                if (now != prev and prev != -1) {
                    adj[prev][now] = min(adj[prev][now], len);
                    adj[now][prev] = min(adj[now][prev], len);
                }
                
                if (!_find) 
                    len++;
                else {
                    prev = now;
                    len = 0;
                }
            }
        }
        
        for (int i = 0; i <= c; i++) {
            int prev = -1, now = -1;
            
            len = 0;
            for (int k = 0; k < r; k++) {
                bool _find = false;
                if (i == c) {
                    if (idx[k][i-1] != -1) {
                        now = idx[k][i-1];
                        _find = true;
                    }
                } else if (i) {
                    if (idx[k][i-1] != -1 or idx[k][i] != -1) {
                        now = (idx[k][i] != -1 ? idx[k][i] : idx[k][i-1]);
                        _find = true;
                    }
                } else {
                    if (idx[k][i] != -1) {
                        now = idx[k][i];
                        _find = true;
                    }
                }
                
                if (now != prev and prev != -1) {
                    adj[prev][now] = min(adj[prev][now], len);
                    adj[now][prev] = min(adj[now][prev], len);
                } 
                
                if (!_find) 
                    len++;
                else {
                    prev = now;
                    len = 0;
                }
            }
        }
        
        int size = 0, ans_len = 0;
        
        using edge = pair<pair<int, int>, int>;
        
        auto cmp = [](edge a, edge b) { return a.S > b.S; };
        priority_queue<edge, vec<edge>, decltype(cmp)> pq(cmp);
        
        for (int i = 0; i < count; i++) {
            for (int k = i+1; k < count; k++) {
                if (adj[i][k] != INF) {
                    pq.emplace(make_pair(i, k), adj[i][k]);
                    // cout << i << " and " << k << " with " << adj[i][k] << endl;
                }
            }
        }
        
        initSet(count);
        
        while (!pq.empty()) {
            auto now = pq.top();
            pq.pop();
            
            if (isSameSet(now.F.F, now.F.S))
                continue;
                
            unionSet(now.F.F, now.F.S);
            
            size++;
            ans_len += now.S;
        }
        
        if (n != 1)
            cout << endl;
        
        cout << "City " << n++ << endl;
        
        if (count <= 1) {
            cout << "No bridges are needed.\n";
        } else if (size == 0) {
            cout << "No bridges are possible.\n";
            cout << count << " disconnected groups\n";
        } else {
            cout << size << (size == 1 ? " bridge" : " bridges") << " of total length " << ans_len << endl;
            
            if (count - size != 1)
                cout << count - size << " disconnected groups\n";
        }
    }
}