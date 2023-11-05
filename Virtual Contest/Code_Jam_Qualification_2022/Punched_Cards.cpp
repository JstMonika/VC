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

int main()
{
    yccc;
    
    int n, t = 1;
    cin >> n;
    
    while (n--) {
        int r, c;
        cin >> r >> c;
        
        cout << "Case #" << t++ << ":\n";
        
        vec<vec<char>> G(2*r+1, vec<char>(2*c+1, '.'));
        
        for (int i = 0; i < 2*r+1; i += 2) {
            for (int k = 0; k < 2*c+1; k++) {
                G[i][k] = (k % 2) ? '-' : '+';
            }
        }
        
        for (int i = 1; i < 2*r+1; i += 2) {
            for (int k = 0; k < 2*c+1; k += 2) {
                G[i][k] = '|';
            }
        }
        
        G[0][0] = G[1][0] = G[0][1] = '.';
        
        for (int i = 0; i < 2*r+1; i++) {
            for (int k = 0; k < 2*c+1; k++) {
                cout << G[i][k];
            }
            
            cout << endl;
        }
    }
}