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
        
        vec<int> _list(n);
        for (auto &i : _list)
            cin >> i;
            
        sort(al(_list), greater<int>());
        
        if (n >= 2 and _list[0] == _list.back()) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
            cout << _list.back();
            for (int i = 0; i < n-1; i++)
                cout << ' ' << _list[i];
            cout << endl;
        }
    }
}