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
        int n, m;
        cin >> n >> m;
        
        vec<int> _list(n);
        for (auto &i : _list) {
            cin >> i;
        }
        
        for (int i = 0; i < m; i++) {
            int tmp;
            cin >> tmp;
            
            sort(al(_list));
            _list[0] = tmp;
        }
        
        ll sum = 0;
        for (auto &i : _list)
            sum += i;
            
        cout << sum << endl;
    }
}