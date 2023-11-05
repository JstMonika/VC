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

#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 0x3f3f3f3f;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

stack<int, vec<int>> total[1005], part[1005], arr[1000005];
deq<bool> is_pop(200005);
vec<string> _map(200005);

int main()
{
    yccc;
    
    int n, m;
    cin >> n >> m;
    
    int count = 0;
    
    int sn = sqrt(n);
    while (m--) {
        int t;
        cin >> t;
        
        if (t == 1) {
            string name;
            int l, r;
            cin >> name >> l >> r;
            
            _map[count] = name;
            
            for (int i = 0; i < n; i += sn) {
                int idx = i / sn;
                
                if (r < i or i+sn-1 < l) continue;
                
                if (l <= i and i+sn-1 <= r) {
                    total[idx].emplace(count);
                } else {
                    part[idx].emplace(count);
                    
                    for (int k = max(l, i); k <= min(r, i+sn-1); k++) {
                        arr[k].emplace(count);
                    }
                }
            }
            
            count++;
        } else if (t == 2) {
            int l, r;
            cin >> l >> r;
            
            int ans = -1;
            for (int i = 0; i < n; i += sn) {
                int idx = i / sn;
                
                if (r < i or i+sn-1 < l) continue;
                
                if (l <= i and i+sn-1 <= r) {
                    while (!total[idx].empty() and is_pop[total[idx].top()]) total[idx].pop();
                    while (!part[idx].empty() and is_pop[part[idx].top()]) part[idx].pop();

                    if (!total[idx].empty()) ans = max(ans, total[idx].top());
                    if (!part[idx].empty()) ans = max(ans, part[idx].top());
                } else {
                    while (!total[idx].empty() and is_pop[total[idx].top()]) total[idx].pop();
                    if (!total[idx].empty()) ans = max(ans, total[idx].top());
                    
                    for (int k = max(l, i); k <= min(r, i+sn-1); k++) {
                        while (!arr[k].empty() and is_pop[arr[k].top()]) arr[k].pop();
                        if (!arr[k].empty()) ans = max(ans, arr[k].top());
                    }
                }
            }
            
            cout << (ans == -1 ? ">_<" : _map[ans]) << endl;
            if (ans != -1) is_pop[ans] = true;
        }
    }
}