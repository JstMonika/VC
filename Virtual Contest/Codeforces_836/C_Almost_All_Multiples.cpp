#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 0x3f3f3f3f;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b = 0, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int n, x;
vec<bool> used;
vec<int> ans;

bool go(int now) {
    if (now > n/2) {
        return true;
    }
    
    for (int i = 2; i <= n/2; i++) {
        if (!used[i] and i % now == 0) {
            used[i] = true;
            ans[now] = i;
            
            if (go(now+1)) return true;
            
            used[i] = false;
        }
    }
    
    if (!used[n] and n % now == 0) {
        used[n] = true;
        ans[now] = n;
        
        if (go(now+1)) return true;
        
        used[n] = false;
    }
    
    return false;
}

int main()
{
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        cin >> n >> x;
        
        if (x > n/2 and x != n) {
            cout << -1 << endl;
            continue;
        }
        
        ans.resize(n+1);
        used.assign(n+1, false);
        used[x] = used[1] = true;
        ans[1] = x, ans[n] = 1;
        
        int upp = n / 2;
        for (int i = upp + 1; i <= n-1; i++) ans[i] = i;
        
        int now = x;
        for (int i = 2; i <= upp; i++) {
            if (i == x) ans[i] = n;
            else ans[i] = i;
        }
        
        while (now <= upp) {
            int next = -1, go = 2 * now;
            while (go <= upp) {
                if (n % go == 0) {
                    next = go;
                    break;
                }
                
                go += now;
            }
            
            if (next == -1) break;
            else {
                swap(ans[now], ans[next]);
                now = next;
            }
        }
        
        if (n % now != 0) {
            cout << -1 << endl;
        } else {
            for (int i = 1; i <= n; i++) {
                cout << ans[i] << ' ';
            }
            cout << endl;
        }
    }
}