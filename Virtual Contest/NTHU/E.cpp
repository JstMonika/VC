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

int match;

int strncmp(string a, string b, int n) {
    match = 0;
    int ret = 0;
    for (int i = 0; i < n; i++) {
        match++;
        if (a[i] != b[i]) break;
        ret++;
    }
    
    cout << a << ' ' << b << ' ' << n << ' ' << ret << ' ' << match << endl;
    return ret;
}

int main()
{
    yccc;
    
    int n;
    cin >> n;
    
    vec<string> str(n);
    for (auto &i : str)
        cin >> i;
    
    int _min = INF, first[2], nextN, ans = 0;
    for (int i = 0; i < n; i++) {
        for (int k = i+1; k < n; k++) {
            int num = min(str[i].size(), str[k].size());
            num = strncmp(str[i], str[k], num);
            
            if (match < _min) {
                _min = match;
                nextN = num;
                first[0] = i;
                first[1] = k;
            }
        }
    }
    
    ans += _min;
    
    vec<int> ANS(2);
    int oriN = nextN;
    for (int z = 0; z < 2; z++) {
        deq<bool> vis(n);
        vis[first[0]] = vis[first[1]] = true;
        nextN = oriN;
        
        string now = str[first[z]];
        int nnextN = nextN, idx;
        for (int i = 0; i < n-2; i++) {
            for (int k = 0; k < n; k++) {
                int num = min(now.size(), str[k].size());
                num = strncmp(str[k], now, min(nextN, num));
                
                if (match < _min) {
                    _min = match;
                    nnextN = num;
                    idx = k;
                }
            }
            
            vis[idx] = true;
            nextN = nnextN;
            ANS[i] += _min;
        }
    }
    
    cout << ans + min(ANS[0], ANS[1]);
    devec(ANS);
}