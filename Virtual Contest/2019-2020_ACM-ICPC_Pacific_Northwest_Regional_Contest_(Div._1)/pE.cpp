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
const int MOD = 11092019;

int main() {
    yccc;
    
    string str;
    cin >> str;
    
    vec<ll> count(26);
    for (auto i : str) {
        count[i - 'a']++;
    }
    
    ll ans = 1;
    for (int i = 0; i < 26; i++) {
        (ans *= count[i]+1) %= MOD;
    }
    
    cout << ans;
}