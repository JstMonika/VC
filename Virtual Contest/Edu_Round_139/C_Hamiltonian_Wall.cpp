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

int main() {
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        int n;
        cin >> n;
        
        int count = 0;
        vec<vec<char>> _list(2, vec<char>(n));
        for (auto &i : _list) {
            for (auto &k : i) {
                cin >> k;
                if (k == 'B') ++count;
            }
        }
        
        vec<p<int>> que;
        for (int i = 0; i < n; i++) {
            if (_list[0][i] == 'B' and _list[1][i] == 'B') continue;
            else if (_list[0][i] == 'B') que.eb(i, 0);
            else que.eb(i, 1);
        }
        
        bool good = true;
        for (int i = 0; i < int(que.size())-1; i++) {
            if (que[i].S != que[i+1].S) {
                if (((que[i+1].F - que[i].F) & 1) != 0) good = false;
            } else {
                if (((que[i+1].F - que[i].F) & 1) == 0) good = false;
            }
        }
        
        cout << (good ? "YES\n" : "NO\n");
    }
}