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

struct Cube {
    bool solid;
    vec<char> dir;
    
    Cube() {}
    
    void init() {
        solid = true;
        
        dir.resize(6);
        fill(al(dir), 0);
    }
};

int n, ans;
Cube cube[10][10][10];

set<tuple<int, int, int>> waiting;
queue<tuple<int, int, int>> que;

bool check(int i, int j, int k) {
    if (any_of(al(cube[i][j][k].dir), [](char ch){ return ch == '.'; })) {
        return false;
    }
    
    set<char> _list;
    for (int z = 0; z < 6; z++)
        _list.insert(cube[i][j][k].dir[z]);
    _list.erase(0);
    
    if (waiting.find(make_tuple(i, j, k)) != waiting.end())
        return true;
    
    return _list.size() <= 1;
}

void push(int i, int j, int k) {
    cube[i][j][k].solid = false;
    ans--;
    
    //* front, left, back, right, top, bottom
     
    int pi = i+1;
    if (cube[i][j][k].dir[4] != 0) {
        for (; pi < n and cube[pi][j][k].solid == false; pi++);
        if (pi < n) {
            cube[pi][j][k].dir[4] = cube[i][j][k].dir[4];
            
            if (!check(pi, j, k)) {
                waiting.emplace(pi, j, k);
                que.emplace(pi, j, k);
            }
        }
    }
    
    pi = i-1;
    if (cube[i][j][k].dir[5] != 0) {
        for (; pi >= 0 and cube[pi][j][k].solid == false; pi--); 
        if (pi >= 0) {
            cube[pi][j][k].dir[5] = cube[i][j][k].dir[5];
            
            if (!check(pi, j, k)) {
                waiting.emplace(pi, j, k);
                que.emplace(pi, j, k);
            }
        }
    }
    
    int pj = j+1;
    if (cube[i][j][k].dir[2] != 0) {   
        for (; pj < n and cube[i][pj][k].solid == false; pj++);
        if (pj < n) {
            cube[i][pj][k].dir[2] = cube[i][j][k].dir[2];
            
            if (!check(i, pj, k)) {
                waiting.emplace(i, pj, k);
                que.emplace(i, pj, k);
            }
        }
    }
    
    pj = j-1;
    if (cube[i][j][k].dir[0] != 0) {
        for (; pj >= 0 and cube[i][pj][k].solid == false; pj--); 
        if (pj >= 0) {
            cube[i][pj][k].dir[0] = cube[i][j][k].dir[0];
            
            if (!check(i, pj, k)) {
                waiting.emplace(i, pj, k);
                que.emplace(i, pj, k);
            }
        }
    }
    
    int pk = k+1;
    if (cube[i][j][k].dir[1] != 0) {
        for (; pk < n and cube[i][j][pk].solid == false; pk++);
        if (pk < n) {
            cube[i][j][pk].dir[1] = cube[i][j][k].dir[1];
            
            if (!check(i, j, pk)) {
                waiting.emplace(i, j, pk);
                que.emplace(i, j, pk);
            }
        }
    }
    
    pk = k-1;
    if (cube[i][j][k].dir[3] != 0) {
        for (; pk >= 0 and cube[i][j][pk].solid == false; pk--); 
        if (pk >= 0) {
            cube[i][j][pk].dir[3] = cube[i][j][k].dir[3];
            
            if (!check(i, j, pk)) {
                waiting.emplace(i, j, pk);
                que.emplace(i, j, pk);
            }
        }
    }
}

int main()
{
    yccc;
    
    while (cin >> n) {
        if (n == 0) break;
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    cube[i][j][k].init();
                
        for (int i = 0; i < n; i++)     //* front, left, back, right, top, bottom
            for (int k = 0; k < 6; k++) {
                switch (k) {
                    case 0:
                        for (int j = 0; j < n; j++)
                            cin >> cube[i][n-1][j].dir[0];
                        break;
                    case 1:
                        for (int j = 0; j < n; j++)
                            cin >> cube[i][j][0].dir[1];
                        break;
                    case 2:
                        for (int j = n-1; j >= 0; j--)
                            cin >> cube[i][0][j].dir[2];
                        break;
                    case 3:
                        for (int j = n-1; j >= 0; j--)
                            cin >> cube[i][j][n-1].dir[3];
                        break;
                    case 4:
                        for (int j = 0; j < n; j++)
                            cin >> cube[0][i][j].dir[4];
                        break;
                    case 5:
                        for (int j = 0; j < n; j++)
                            cin >> cube[n-1][n-1-i][j].dir[5];
                        break;
                }
            }
            
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++)
                    if (!check(i, j, k)) {
                        waiting.emplace(i, j, k);
                        que.emplace(i, j, k);
                    }
        
        ans = n*n*n;
        while (!que.empty()) {
            int i, j, k;
            tie(i, j, k) = que.front();
            que.pop();
            
            if (waiting.find(make_tuple(i, j, k)) != waiting.end()) {
                waiting.erase(make_tuple(i, j, k));   
                push(i, j, k);
            }
        }
        
        // for (int i = 0; i < n; i++)
        //     for (int j = 0; j < n; j++) {
        //         for (int k = 0; k < n; k++) {
        //             cout << (cube[i][j][k].solid ? 'o' : 'x');
        //             for (int z = 0; z < 6; z++)
        //                 cout << (cube[i][j][k].dir[z] == 0 ? '-' : cube[i][j][k].dir[z]);
                    
        //             cout << " \n"[k == n-1];
        //         }
                
        //         if (j == n-1)
        //             cout << "\n\n";
        //     }
        // cout << flush;
        
        cout << "Maximum weight: " << ans << " gram(s)" << endl;
    }
}