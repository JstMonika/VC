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
        
        int a1;
        vec<int> _list(n-1);
        
        cin >> a1;
        for (auto &i : _list)
            cin >> i;
            
        sort(al(_list));
        
        for (int i = 0; i < n-1; i++) {
            if (_list[i] > a1) {
                int dif = _list[i] - a1;
                
                a1 += (dif + 1) / 2;
            }
        }
        
        cout << a1 << endl;
    }
}