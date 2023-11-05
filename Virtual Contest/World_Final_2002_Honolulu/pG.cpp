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

int w, h;

vec<vec<char>> ansi;

void fix() {
    for (int t = 0; t < 2 * w * h; t++) {
        for (int i = 1; i < h+1; i++) {
            for (int k = 1; k < 2*w; k++) {
                if (ansi[i][k] == '_' and i != h) {
                    if (!((ansi[i][k+1] == '|' and ansi[i+1][k+1] == '|') or ansi[i][k+2] == '_')) ansi[i][k] = ' ';
                    if (!((ansi[i][k-1] == '|' and ansi[i+1][k-1] == '|') or ansi[i][k-2] == '_')) ansi[i][k] = ' ';
                } else if (ansi[i][k] == '|') {
                    if (!((ansi[i][k+1] == '_' and ansi[i][k-1] == '_') or (i != h and ansi[i+1][k] == '|'))) ansi[i][k] = ' ';
                    if (!((ansi[i-1][k+1] == '_' and ansi[i-1][k-1] == '_') or ansi[i-1][k] == '|')) ansi[i][k] = ' ';
                }
            }
        }
    }
}

int main()
{
    yccc;
   
    int c = 1;
    while (cin >> w >> h) {
        if (w == 0) break;
        
        cin.get();
        
        vec<vec<char>> a(h+1), b(h+1), ansu(h+1, vec<char>(2*w+1));
        for (int i = 0; i < h+1; i++) {
            for (int k = 0; k < 2*w+1; k++) {
                a[i].eb(cin.get());
            }
            
            cin.get();
            
            for (int k = 0; k < 2*w+1; k++) {
                b[i].eb(cin.get());
            }
            
            cin.get();
        }
        
        ansi.resize(h+1);
        for (int i = 0; i < h+1; i++) {
            ansi[i].resize(2*w+1);
            for (int k = 0; k < 2*w+1; k++) {
                ansu[i][k] = (a[i][k] == ' ' ? b[i][k] : a[i][k]);
                ansi[i][k] = (a[i][k] == b[i][k] ? a[i][k] : ' ');
            }
        }
        
        fix();
        
        cout << "Case " << c++ << ":\n";
        for (int i = 0; i < h+1; i++) {
            for (int k = 0; k < 2*w+1; k++)
                cout << ansu[i][k];
            
            cout << ' ';
            
            for (int k = 0; k < 2*w+1; k++)
                cout << ansi[i][k];
            
            cout << endl;
        }
        
        cout << endl;   
    }
}