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

#define idx(x) (x + 101)

#define UP 0
#define LEFT 1
#define DOWN 2
#define RIGHT 3

struct Node {
    int dir, level;
    bool vis;
    
    Node() {
        dir = level = -1;
        vis = false;
    }
    
    Node(int dir, int level) : dir(dir), level(level) {
        vis = false;
    }
};

int main()
{
    yccc;
    
    int c = 1, T;
    cin >> T;
    
    while (T--) {
        int n, m, d;
        cin >> n >> m >> d;
        
        vec<vec<vec<Node>>> _map(220, vec<vec<Node>>(220));
        
        int x = 0, y = 0, count = 0;
        for (int i = 0; i < n; i++) {
            int tx, ty;
            cin >> tx >> ty;
            
            while (x != tx or y != ty) {
                if (x == tx) {
                    if (y < ty) {
                        _map[idx(x)][idx(y)].eb(UP, count++);
                        y++;
                    }
                    else {
                        _map[idx(x)][idx(y)].eb(DOWN, count++);
                        y--;
                    }
                } else {
                    if (x < tx) {
                        _map[idx(x)][idx(y)].eb(RIGHT, count++);
                        x++;
                    }
                    else {
                        _map[idx(x)][idx(y)].eb(LEFT, count++);
                        x--;
                    }
                }
            }
        }
        
        vec<vec<int>> antMap(220, vec<int>(220, -1));
        deq<bool> done(m);
        vec<int> ans;
        vec<pii> antPos(m);
        
        int t = 0, gen = 0;
        while (true) {
            //* move ants.
            
            deq<bool> move(gen);
            bool good;
            do {
                good = false;
                
                for (int i = 0; i < gen; i++) {
                    if (done[i] or move[i]) continue;
                    
                    int px = antPos[i].F, py = antPos[i].S;
                    
                    if (_map[idx(px)][idx(py)].size() == 0) {
                        ans.eb(i);
                        done[i] = true;
                    } else {
                        if (none_of(al(_map[idx(px)][idx(py)]), [](Node src) { return src.vis; })) { //* first ant.
                            //* go first one.
                        } else {   
                            for (int k = _map[idx(px)][idx(py)].size() - 1; k >= 0; k--) {
                                if (_map[idx(px)][idx(py)][k].vis) {
                                    int dir = _map[idx(px)][idx(py)].dir;
                                    //* go this one.
                                    
                                    int gx[4] = {0, -1, 0, 1}, gy[4] = {1, 0, -1, 0};
                                    
                                    if (antMap[idx(px) + gx[dir]][idx(py) + gy[dir]] == -1) {
                                        move[i] = true;
                                        
                                        antMap[idx(px) + gx[dir]][idx(py) + gy[dir]] = i;
                                        antMap[idx(px)][idx(py)] = -1;
                                        antPos[i] = make_pair(idx(px) + gx[dir], idx(py) + gy[dir]);
                                    }
                                }
                            }
                        }
                    }
                }
            } while (!good);
            
                        
            //* generate ants.
            if (t >= gen * d) {
                if (antMap[idx(0)][idx(0)] == -1) {
                    antMap[idx(0)][idx(0)] = gen;
                    antPos[gen] = make_pair(0, 0);
                    
                    gen++;
                }
            }
        }
    }
}