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

ll n, m, ans, MASK, queen;

void go(int row, int qL, int M, int qR, int rL, int rR, int queen, int rock) {
    if (queen == n and rock == m) {
        ans++;
        return;
    } else if (row == m+n) return;
    
    int valid = ~(rL | M | rR) & MASK, next;
    // cout << bitset<32>(valid).to_string() << endl;
    for (; valid != 0; valid ^= next) {
        next = valid & (~valid + 1);
        int idx = __lg(next);
        
        if (queen != n and ~(qL | qR) & (1 << idx)) {
            go(row+1, (qL | (1<<idx)) << 1, M | (1<<idx), (qR | (1<<idx)) >> 1, (rL | (1<<idx)) << 1, (rR | (1<<idx)) >> 1, queen+1, rock);
        }
        
        if (rock != m) {
            go(row+1, (qL | (1<<idx)) << 1, M | (1<<idx), (qR | (1<<idx)) >> 1, rL << 1, rR >> 1, queen, rock+1);
        }
    }
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        ans = 0;
        
        cin >> n >> m;
        MASK = (1<<(n+m)) - 1;
        
        go(0, 0, 0, 0, 0, 0, 0, 0);
        
        cout << ans << endl;
    }
}