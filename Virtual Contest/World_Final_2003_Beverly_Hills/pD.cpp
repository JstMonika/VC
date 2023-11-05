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

struct Country {
    string name;
    int sx, sy, ex, ey;
    int time;
    
    Country() {
        time = -1;
    }
};

int main()
{
    yccc;
    
    int n, c = 1;
    while (cin >> n) {
        if (!n) break;
        
        vec<Country> _list(n);
        for (auto &i : _list)
            cin >> i.name >> i.sx >> i.sy >> i.ex >> i.ey;
        
        vec<vec<vec<int>>> _map(n, vec<vec<int>>(12, vec<int>(12, -1)));
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                for (int si = _list[k].sx; si <= _list[k].ex; si++)
                    for (int sk = _list[k].sy; sk <= _list[k].ey; sk++)
                        _map[i][si][sk] = (i == k ? 1000000 : 0);
        
        vec<pair<int, string>> ans;
        
        int t = 0;
        while (true) {
            for (int i = 0; i < n; i++) {
                if (_list[i].time != -1)
                    continue;
                        
                bool good = true;
                for (int k = 0; k < n; k++)
                    for (int si = _list[i].sx; si <= _list[i].ex; si++)
                        for (int sk = _list[i].sy; sk <= _list[i].ey; sk++)
                            if (_map[k][si][sk] == 0) good = false;
                
                if (good) {
                    _list[i].time = t;
                    ans.eb(t, _list[i].name);
                }
            }
            
            bool good = true;
            for (int i = 0; i < n; i++)
                if (_list[i].time == -1) good = false;
                
            if (good) break;
            
            auto tmp = _map;
            
            for (int i = 0; i < n; i++) {
                for (int si = 1; si <= 10; si++) {
                    for (int sk = 1; sk <= 10; sk++) {
                        int _count = 0;
                        
                        if (tmp[i][si-1][sk] != -1) {
                            tmp[i][si-1][sk] += _map[i][si][sk] / 1000;
                            _count++;
                        }
                        if (tmp[i][si+1][sk] != -1) {
                            tmp[i][si+1][sk] += _map[i][si][sk] / 1000;
                            _count++;
                        }
                        if (tmp[i][si][sk-1] != -1) {
                            tmp[i][si][sk-1] += _map[i][si][sk] / 1000;
                            _count++;
                        }
                        if (tmp[i][si][sk+1] != -1) {
                            tmp[i][si][sk+1] += _map[i][si][sk] / 1000;
                            _count++;
                        }
                        
                        tmp[i][si][sk] -= _map[i][si][sk] / 1000 * _count;
                    }
                }
            }
            
            _map = tmp;
            
            t++;
        }
        
        sort(al(ans));
        
        cout << "Case Number " << c++ << endl;
        for (int i = 0; i < ans.size(); i++) {
            cout << "   " << ans[i].S << "   " << ans[i].F << endl;
        }
    }
}