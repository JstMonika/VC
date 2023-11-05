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

int n, m;
const ll INF = 1e18;
vec<int> _list, color;

struct pairhash {
    template<typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& x) const {
        return std::hash<T>()(x.F) ^ std::hash<U>()(x.S);
    }
};

unordered_map<pair<int, ll>, ll, pairhash> _map;

ll solve(int now, ll active) {
    if (_map.find(make_pair(now, active)) != _map.end()) {
        return _map[make_pair(now, active)];
    } else if (now == n-1) {
        return 0;
    }
    
    ll ans = INF;
    
    if (now + 2 <= n-1) {
        if (active & (1ll << _list[now+2])) {
            ans = min(ans, solve(now+2, active));
        } else {
            ans = min(ans, solve(now+2, active | (1ll << _list[now+2])) + color[_list[now+2]]);
        }
    }
    
    if (active & (1ll << _list[now+1])) {
        ans = min(ans, solve(now+1, active));
    } else {
        ans = min(ans, solve(now+1, active | (1ll << _list[now+1])) + color[_list[now+1]]);
    }
            
    _map[make_pair(now, active)] = ans;
    
    return ans;
}

int main() {
    yccc;
    
    cin >> n >> m;
    
    _list.resize(n);
    for (auto &i : _list) {
        cin >> i;
        i--;
    }
        
    color.resize(m);
    for (auto &i : color)
        cin >> i;
        
    cout << solve(0, (1ll<<_list[0])) + color[_list[0]];
}