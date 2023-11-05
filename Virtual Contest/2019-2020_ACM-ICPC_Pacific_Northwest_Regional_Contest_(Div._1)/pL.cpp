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

vec<int> ans;
string str;
void go(int now, vec<int> tmp) {
    if (now == str.size()) {
        tmp.resize(str.size());
        reverse(al(tmp));
        
        if (ans.size() == 0) {
            ans = tmp;
        } else {
            for (int i = 0; i < str.size(); i++) {
                if (tmp[i] < ans[i]) {
                    ans = tmp;
                    return;
                } else if (tmp[i] > ans[i]) return;
            }
        }
        
        return;
    }
    
    for (int i = 0; i <= 9; i++) {
        tmp[now] = i;
        
        int num = 0;
        for (int k = 0; k <= now; k++) {
            num += tmp[k] * tmp[now-k];
        }
        
        if (num % 10 == str[now] - '0') {
            go(now+1, tmp);
        }
    }
}

int main() {
    yccc;
    
    cin >> str;
    
    reverse(al(str));
    
    go(0, vec<int>(str.size()));
    
    if (ans.size() == 0) {
        cout << -1;
        return 0;
    }
    
    bool first = false;
    for (auto i : ans) {
        if (i != 0) first = true;
        
        if (first or i != 0) cout << i;
    }
}