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
        int n, k, sub = 0, damage = 0;
        cin >> n >> k;
        
        auto cmp = [](p<int>& a, p<int>& b) -> bool {
            return a.F > b.F;
        };
        
        priority_queue<p<int>, vec<p<int>>, decltype(cmp)> pq(cmp);
        map<int, int> _map;
        
        vec<p<int>> _list(n);
        for (auto &i : _list) {
            cin >> i.F;
        }
        for (auto &i : _list) {
            cin >> i.S;
        }
        
        for (auto &i : _list) {
            pq.emplace(i);
            
            _map[i.S]++;
        }
        
        bool good = false;
        while (sub < k) {
            damage += k;
            
            // cout << damage << endl;
            while (!pq.empty() and pq.top().F <= damage) {
                _map[pq.top().S]--;
                
                if (_map[pq.top().S] == 0) _map.erase(pq.top().S);
                
                // cout << pq.top().S << " dead\n";
                
                pq.pop();
            }
            
            if (pq.empty()) {
                good = true;
                break;
            }
            
            // cout << "sub: " << (*_map.begin()).F << endl;
            k -= (*_map.begin()).F;
        }
        
        cout << (good ? "YES\n" : "NO\n");
    }
}