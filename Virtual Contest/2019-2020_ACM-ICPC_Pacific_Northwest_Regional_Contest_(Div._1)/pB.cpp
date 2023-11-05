#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template <typename T> using vec = vector<T>;
template <typename T> using deq = deque<T>;
template <typename T> using p = pair<T, T>;

#define endl '\n'
#define F first
#define S second
#define eb emplace_back
#define al(a) a.begin(),a.end()
#define yccc ios_base::sync_with_stdio(false),cin.tie(0)

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (abs(a-b) < eps) return 0;
    return a-b;
}

const double PI = acos(-1);

int main() {
    yccc;
    
    int n, k;
    cin >> n >> k;
    
    vec<int> _list(n), last(n), count(n+1);
    for (auto &i : _list) {
        cin >> i;
    }
    
    for (int i = n-1; i >= 0; i--) {
        last[i] = ++count[_list[i]];
    }
    
    deq<int> d;
    vec<int> ans;
    deq<bool> isv(n+1);
    fill(isv.begin(), isv.end(), false);
    
    for (int i = 0; i < n; i++) {
        //printf("visit %d\n",i);
        if(isv[_list[i]]) continue;

        while (!d.empty()) {
            if(d.back() >= _list[i]) {
                d.pop_back();
            } else break;               
        }
        
        d.eb(_list[i]);

        if (last[i] == 1) {
            while(!d.empty()) {
                ans.eb(d.front());
                isv[d.front()] = true;
                d.pop_front();
            }
        } 
    }

    for(int i=0;i<k;i++) cout<<ans[i] << " \n"[i==k-1];
}