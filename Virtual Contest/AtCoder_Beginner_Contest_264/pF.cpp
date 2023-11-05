#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define dbg

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

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

int main()
{
    yccc;
    
    int r, c;
    cin >> r >> c;
    vec<int> rp(r), cp(c);
    for (auto &i : rp)
        cin >> i;
    for (auto &i : cp)
        cin >> i;
    
    deq<deq<bool>> G(r, deq<bool>(c));
    cin.get();
    for (auto &i : G) {
        for (auto &k : i) {
            k = (cin.get() - '0');
        }
        cin.get();
    }
    
    // devec2(G);
    
    vec<vec<vec<ll>>> dp(r, vec<vec<ll>>(c, vec<ll>(4, llINF)));
    
    for (int r = 0; r < 4; r++) {
        if (G[0][0] == 1) {   
            if (r == 1)
                dp[0][0][r] = rp[0];
            else if (r == 2)
                dp[0][0][r] = cp[0];
        } else {
            if (r == 0)
                dp[0][0][r] = 0;
            else if (r == 3)
                dp[0][0][r] = rp[0] + cp[0];
        }
            
    }
    
    //* from here.
    for (int i = 1; i < r; i++)
        for (int z = 0; z < 4; z++) {
            if ((z == 0 or z == 3) and G[i][0]) continue;
            if ((z == 1 or z == 2) and !G[i][0]) continue;
            
            if (G[i-1][0]) {
                if (z == 0 or z == 1)
                    dp[i][0][z] = min(dp[i][0][z], dp[i-1][0][1] + rp[i]);
                if (z == 2 or z == 3)
                    dp[i][0][z] = min(dp[i][0][z], dp[i-1][0][2] + rp[i]);
            } else {
                if (z == 0 or z == 1)
                    dp[i][0][z] = min(dp[i][0][z], dp[i-1][0][0] + rp[i]);
                if (z == 2 or z == 3)
                    dp[i][0][z] = min(dp[i][0][z], dp[i-1][0][3] + rp[i]);
            }
        }
        
    for (int i = 1; i < c; i++)
        for (int z = 0; z < 4; z++) {
            if ((z == 0 or z == 3) and G[0][i]) continue;
            if ((z == 1 or z == 2) and !G[0][i]) continue;
            
            if (G[0][i-1]) {
                if (z == 1 or z == 3)
                    dp[0][i][z] = min(dp[0][i][z], dp[0][i-1][1] + cp[i]);
                if (z == 0 or z == 2)
                    dp[0][i][z] = min(dp[0][i][z], dp[0][i-1][2] + cp[i]);
            } else {
                if (z == 0 or z == 2)
                    dp[0][i][z] = min(dp[0][i][z], dp[0][i-1][0] + cp[i]);
                if (z == 1 or z == 3)
                    dp[0][i][z] = min(dp[0][i][z], dp[0][i-1][3] + cp[i]);
            }
        }
    
    for (int i = 1; i < r; i++) {
        for (int k = 1; k < c; k++) {
            if (i == 0 and k == 0) continue;
            
            for (int z = 0; z < 4; z++) {
                if ((z == 0 or z == 3) and G[i][k]) continue;
                if ((z == 1 or z == 2) and !G[i][k]) continue;
                
                for (int pre = 0; pre < 4; pre++) {
                    if (i-1 >= 0/* and G[i-1][k] == (z == 1 or z == 3)*/) {
                        if (pre / 2 != z / 2) continue;
                        
                        dp[i][k][z] = min(dp[i][k][z], dp[i-1][k][pre] + (z == 3 ? rp[i] : 0));
                    }
                    
                    if (k-1 >= 0/* and G[i][k-1] == (z == 2 or z == 3)*/) {
                        if (pre % 2 != z % 2) continue;
                        
                        dp[i][k][z] = min(dp[i][k][z], dp[i][k-1][pre] + (z == 3 ? cp[k] : 0));
                    }
                }
            }
        }
    }
 
    for (int z = 0; z < 4; z++) {   
        for (int i = 0; i < r; i++) 
            for (int k = 0; k < c; k++) {
                cout << dp[i][k][z] << " \n"[k == c-1];
            }
            
        cout << endl;
    }
    
    ll ans = llINF;
    for (int z = 0; z < 4; z++)
        ans = min(ans, dp[r-1][c-1][z]);
    cout << ans;
        
}