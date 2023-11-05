#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n, k;
vec<int> cont;
deq<bool> vis;
vec<p<int>> _list;

int ans;
void dfs(int count) {
    // devec(vis);
    if (all_of(al(vis), [](bool src){ return src == true; })) {
          ans = min(count, ans);
        //   cout << "done\n";
          return;      
    }
    
    vec<int> next;
    int _max = 0, now = 0;
    for (int i = 0; i <= k; i++) {
        now += cont[i];
        
        if (now > _max) {
            _max = now;
            next.clear();
        }
        
        if (now == _max)
            next.eb(i);
    }
    
    for (auto z : next) {    
        vec<int> mark;
        for (int i = 0; i < n; i++) {
            if (!vis[i] and _list[i].F <= z and z <= _list[i].S) {
                vis[i] = true;
                
                cont[_list[i].F]--;
                cont[_list[i].S+1]++;
                
                mark.eb(i);
            }
        }
        
        dfs(count+1);
        
        for (auto g : mark) {
            vis[g] = false;
            
            cont[_list[g].F]++;
            cont[_list[g].S+1]--;
        }
    }
}

int main()
{
    yccc;
    
    cin >> n >> k;
    
    cont.resize(k+2);
    vis.resize(n);
    _list.resize(n);
    
    for (auto &i : _list) {
        cin >> i;
        cont[i.F]++;
        cont[i.S+1]--;
    }
    
    ans = INF;
    
    dfs(0);
    
    cout << ans << endl;
}