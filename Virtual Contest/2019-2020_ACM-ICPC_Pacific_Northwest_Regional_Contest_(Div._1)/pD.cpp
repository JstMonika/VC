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

    int a, b;
    cin >> a >> b;
    
    ll count = 0;
    while (a > b) {
        if (a % 2) {
            a++;
            count++;
            continue;
        }
        
        a /= 2;
        count++;
    }
    
    cout << count + (b-a) << endl;
}