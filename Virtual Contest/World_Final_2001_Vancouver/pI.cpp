#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
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

const int INF = numeric_limits<int>::max();
const int nINF = numeric_limits<int>::min();
const ll llINF = numeric_limits<long long>::max();
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

struct Path {
    char ch;
    int x, y;
    char move;
    
    Path(char ch, int x, int y, char move) : ch(ch), x(x), y(y), move(move) {}
};

struct Maze {
    int r, c;
    bool solved, valid;
    
    vec<vec<char>> G;
    vec<int> count;
    vec<Path> path;
    
    string str() {
        string ret;
        
        for (auto i : G) {
            for (auto k : i)
                ret += k;
        }
        
        return ret;
    }
    
    bool drop() {
        bool first = false;
        bool _find = false;
        
        do {
            _find = false;
            
            for (int i = 0; i < r-1; i++) {
                for (int k = 1; k < c-1; k++) {
                    if (isalpha(G[i][k]) and G[i+1][k] == '-') {
                        swap(G[i][k], G[i+1][k]);
                        
                        first = true;
                        _find = true;
                    }
                }
            }
            
        } while (_find);
        
        return first;
    }
    
    bool can_clear(int i, int k) {
        if (!isalpha(G[i][k]))
            return false;
            
        int gx[4] = {0, -1, 0, 1};
        int gy[4] = {1, 0, -1, 0};
        
        for (int m = 0; m < 4; m++) {
            int x = i + gx[m], y = k + gy[m];
            
            if (x < 0 or x >= r)
                continue;
            if (y < 0 or y >= c)
                continue;
            
            if (G[x][y] == G[i][k])
                return true;
        }
        
        return false;
    }
    
    void clear(int i, int k, int pi, int pk) {
        int gx[4] = {0, -1, 0, 1};
        int gy[4] = {1, 0, -1, 0};
        
        for (int m = 0; m < 4; m++) {
            int x = i + gx[m], y = k + gy[m];
            
            if (x < 0 or x >= r)
                continue;
            if (y < 0 or y >= c)
                continue;
            
            if (G[x][y] == G[i][k] and (make_pair(x, y) != make_pair(pi, pk)))
                clear(x, y, i, k);
        }
        
        G[i][k] = '-';
    }
    
    void clear() {
        for (int i = 0; i < r; i++)
            for (int k = 0; k < c; k++)
                if (can_clear(i, k))
                    clear(i, k, -1, -1);
    }
    
    Maze(int r, int c) : r(r), c(c) {
        count.resize(26);
        
        G.resize(r);
        for (int i = 0; i < r; i++) {
            G[i].resize(c);
            
            string tmp;
            cin >> tmp;
            
            for (int k = 0; k < c; k++) {
                G[i][k] = tmp[k];
                
                if (isalpha(tmp[k])) {
                    count[tmp[k] - 'A']++;
                }
            }
        }
        
        solved = all_of(al(count), [](int i) { return i == 0; });
        valid = true;
    }
    
    Maze(const Maze& src, pii pos, bool dir) { //* dir: 0: left, 1: right.
        *this = src;
        
        path.eb(G[pos.F][pos.S], pos.F, pos.S, (dir ? 'R' : 'L'));
        
        swap(G[pos.F][pos.S], G[pos.F][pos.S + (dir ? 1 : -1)]);
        
        drop();
        do {
            clear();
        } while (drop());
        
        fill(al(count), 0);
        for (int i = 0; i < r; i++) {
            for (int k = 0; k < c; k++) {
                if (isalpha(G[i][k]))
                    count[G[i][k] - 'A']++;
            }
        }
        
        solved = all_of(al(count), [](int i) { return i == 0; });
        valid = all_of(al(count), [](int i) { return i != 1; });
    }
};

ostream& operator<<(ostream& out, Maze src) {
    for (int i = 0; i < src.r; i++) {
        for (int k = 0; k < src.c; k++) {
            cout << src.G[i][k];
        }
        cout << endl;
    }
    
    for (int i = 0; i < src.path.size(); i++) {
        cout << src.path[i].ch << src.path[i].x << src.path[i].y << src.path[i].move << ' ';
    }
    cout << endl;
    
    cout << flush;
    
    return out;
}

int main()
{
    yccc;
    
    int r, c;
    string name;
    
    while (cin >> r >> c >> name) {
        if (r == 0) 
            break;
            
        Maze maze(r, c);
        
        unordered_set<string> _set;
        queue<Maze> que;
        que.emplace(maze);
        _set.insert(maze.str());
        
        while (!que.empty()) {
            auto now = que.front();
            que.pop();
            
            // cout << now << endl;
            // cout << flush;
            
            if (now.solved) {
                cout << name << ": Minimum solution length = " << now.path.size() << endl;
                
                int count = 1;
                for (auto i : now.path) {
                    cout << "(" << i.ch << "," << i.x << "," << i.y << "," << i.move << ")";
                    cout << " \n"[count++ % 4 == 0];
                }
                
                if ((count-1) % 4 != 0)
                    cout << endl;
                
                break;
            }
            
            //* emplace all move.
            for (int i = 0; i < r-1; i++) {
                for (int k = 1; k < c-1; k++) {
                    if (isalpha(now.G[i][k]) and now.G[i][k+1] == '-') {
                        auto next = Maze(now, make_pair(i, k), 1);
                        
                        if (next.valid and _set.find(next.str()) == _set.end()) {
                            que.emplace(next);
                            _set.insert(next.str());
                        }
                    }
                    
                    if (isalpha(now.G[i][k]) and now.G[i][k-1] == '-') {
                        auto next = Maze(now, make_pair(i, k), 0);
                        
                        if (next.valid and _set.find(next.str()) == _set.end()) {
                            que.emplace(next);
                            _set.insert(next.str());
                        }
                    }
                }
            }
        }
    }
}