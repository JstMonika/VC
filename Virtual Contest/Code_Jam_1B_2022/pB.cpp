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

void print(__int128 src) {
    vec<int> _list;
    
    do {
        _list.eb(src % 10);
        src /= 10;
    } while (src != 0);
    
    for (int i = _list.size()-1; i >= 0; i--)
        cout << _list[i];
}

int main()
{
    yccc;
    
    int c = 1, t;
    cin >> t;
    
    while (t--) {
        int n, q;
        cin >> n >> q;
        
        vec<vec<int>> _list(n, vec<int>(q));
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < q; k++)
                cin >> _list[i][k];
                
            sort(al(_list[i]));
        }
        
        vec<int> tmp = {_list[0][q-1]};
        _list[0] = tmp;
        
        __int128 ans = _list[0][q-1];
        
        vec<vec<__int128>> dp(n+1, vec<__int128>(2));
        dp[0][0] = dp[0][1] = _list[0][q-1];
        
        // print(dp[0][0]);
        // cout << endl;
        
        for (int i = 1; i < n; i++) {
            // print(min(dp[i-1][0] + abs(_list[i-1][0] - _list[i][q-1]), dp[i-1][1] + abs(_list[i-1][q-1] - _list[i][q-1])));
            // print(min(dp[i-1][0] + abs(_list[i-1][0] - _list[i][0]), dp[i-1][1] + abs(_list[i-1][q-1] - _list[i][0])));
            // cout << endl;
            
            dp[i][0] = min(dp[i-1][0] + abs(_list[i-1][0] - _list[i][q-1]), dp[i-1][1] + abs(_list[i-1][q-1] - _list[i][q-1])) + (_list[i][q-1] - _list[i][0]);
            dp[i][1] = min(dp[i-1][0] + abs(_list[i-1][0] - _list[i][0]), dp[i-1][1] + abs(_list[i-1][q-1] - _list[i][0])) + (_list[i][q-1] - _list[i][0]);
            
            // print(dp[i][0]);
            // cout << endl;
            // print(dp[i][1]);
            // cout << endl;
        }
        
        cout << "Case #" << c++ << ": ";
        print(min(dp[n-1][0], dp[n-1][1]));
        cout << endl;
    }
}