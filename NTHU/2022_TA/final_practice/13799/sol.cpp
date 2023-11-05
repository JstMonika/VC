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
    
    vec<int> _list(n), count(k+1);
    for (auto &i : _list)
        cin >> i;
        
    int len = 0, now = 0, ans = 0;
    
    for (int i = 0; i < n; i++) {
        if (++count[_list[i]] != 1) {
            len++;
            
            while (true) {
                count[_list[now]]--;
                len--;
                
                now++;
                if (_list[now-1] == _list[i]) break;
            }
        } else {
            len++;
        }
        
        if (len == k)
            ans++;
    }
    
    cout << ans << endl;
}