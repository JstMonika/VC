#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

int n, m, k;
vec<vec<char>> _list, goal;
vec<int> ans;
int cont;

bool same() {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            if (_list[i][k] != goal[i][k]) return false;
        }
    }
    
    return true;
}

void go(int i, int k, int s) {
    if (s == 0) {
        if (same()) {
            cont++;
        }
         
        return;
    }
    
    int gx[4] = {-1, -1, 1, 1};
    int gy[4] = {1, -1, 1, -1};
        
    for (int z = 0; z < 4; z++) {
        if (i + gx[z] < 0 or i + gx[z] >= n) continue;
        if (k + gy[z] < 0 or k + gy[z] >= m) continue;
        
        // cout << i << ' ' << k << ' ' << z << endl << flush;
        swap(_list[i][k], _list[i+gx[z]][k+gy[z]]);
        ans.eb(z);
        go(i+gx[z], k+gy[z], s-1);
        ans.pop_back();
        swap(_list[i][k], _list[i+gx[z]][k+gy[z]]);
    }
}

int main() {
    yccc;
    
    cin >> n >> m >> k;
    _list.assign(n, vec<char>(m));
    goal.assign(n, vec<char>(m));
    
    int I, K;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            cin >> _list[i][k];
            if (_list[i][k] == 'x') I = i, K = k;
        }
    }
    
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < m; k++) {
            cin >> goal[i][k];
        }
    }
    
    go(I, K, k);
    
    cout << cont << endl;
}