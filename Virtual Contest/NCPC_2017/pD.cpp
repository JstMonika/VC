#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

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

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int n, k;
    cin >> n >> k;
    
    int _max = 0, ans;
    
    unordered_map<ll, int> _map;
    queue<ll> que;
    for (int i = 0; i < n; i++) {
        string str;
        cin >> str;
        
        bitset<20> tmp(str);
        que.emplace(tmp.to_ullong());
        _map[tmp.to_ullong()] = 0;
    }
    
    while (!que.empty()) {
        auto now = que.front();
        que.pop();
        
        for (int i = 0; i < k; i++) {
            if (_map.find(now ^ (1ll<<i)) == _map.end()) {
                que.emplace(now ^ (1ll<<i));
                _map[now ^ (1ll<<i)] = _map[now] + 1;
                
                if (_map[now] + 1 > _max) {
                    _max = _map[now] + 1;
                    ans = now ^ (1ll<<i);
                }          
            }
        }
    }
    
    cout << bitset<20>(ans).to_string().substr(20-k) << endl;
}