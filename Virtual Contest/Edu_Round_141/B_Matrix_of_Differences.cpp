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
        
        vec<vec<int>> _list(n, vec<int>(n));
        
        int i = 0, k = 0;
        bool inc = true, lower = true;
        int l = 1, r = n * n;
        
        while (i < n) {
            _list[i][k] = lower ? l++ : r--;
            lower = !lower;
            
            if (inc) {
                k++;
                if (k == n) {
                    k--, i++;
                    inc = !inc;
                }
            } else {
                k--;
                if (k < 0) {
                    k++, i++;
                    inc = !inc;
                }
            }
        }
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++)
                cout << _list[i][k] << " \n"[k == n-1];
    }
}