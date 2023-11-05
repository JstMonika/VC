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
    
    int n, k;
    cin >> n >> k;
    
    vec<int> _list(n);
    for (auto &i : _list)
        cin >> i;
    
    for (int i = 0; i < n; i++) {
        for (int k = i+1; k < n; k++) {
            if (_list[i] < _list[k])
                swap(_list[i], _list[k]);
        }
    }
    
    ll sum = 0;
    for (int i = 0; i < k; i++)
        sum += _list[i];
        
    cout << sum << endl;
}