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
        vec<p<int>> _list(3);
        for (auto &i : _list)
            cin >> i.F >> i.S;
            
        if (_list[0].F != _list[1].F and _list[1].F != _list[2].F and _list[2].F != _list[0].F)
            cout << "YES\n";
        else if (_list[0].S != _list[1].S and _list[1].S != _list[2].S and _list[2].S != _list[0].S)
            cout << "YES\n";
        else cout << "NO\n";
    }
}