#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int _list[10000][10000] = {0}, shortcut[10000][10000];

int n;
bool in(int x) {
    return x >= 0 and x < n;
}

int main()
{
    yccc;
    
    int t, c = 1;
    cin >> t;
    
    while (t--) {
        
        int q;
        cin >> n >> q;
        
        q = n * n - 1 - q;
        
        memset(_list, 0, sizeof(_list));
        memset(shortcut, 0, sizeof(shortcut));
        
        int i = 0, k = 0, count = 1;
        
        bool good = false;
        while (true) {
            good = false;
            
            while (k < n and _list[i][k] == 0) {
                good = true;
                _list[i][k++] = count++;
            }
            
            k--, i++;
            
            while (i < n and _list[i][k] == 0) {
                good = true;
                _list[i++][k] = count++;
            }
            
            i--, k--;
            
            while (k >= 0 and _list[i][k] == 0) {
                good = true;
                _list[i][k--] = count++;
            }
            
            k++, i--;
            
            while (i >= 0 and _list[i][k] == 0) {
                good = true;
                _list[i--][k] = count++;
            }
            
            i++, k++;
            
            if (!good) break;
        }
        
        int gx[4] = {0, 0, 1, -1}, gy[4] = {1, -1, 0, 0};
        
        for (int i = 0; i < n; i++)
            for (int k = 0; k < n; k++) {
                for (int m = 0; m < 4; m++) {
                    if (in(i + gx[m]) and in(k + gy[m]) and _list[i + gx[m]][k + gy[m]] - _list[i][k] > 1)
                        shortcut[i][k] = _list[i + gx[m]][k + gy[m]] - _list[i][k] - 1;
                }
            }
        
        
        
        cout << "Case #" << c++ << ": ";
    }
}