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
    
    int n;
    cin >> n;
    
    while (n--) {
        int r, c;
        cin >> r >> c;
        
        vec<vec<vec<char>>> _map(4, vec<vec<char>>(4, vec<char>(4, '.')));
        
        for (int i = 0; i < 4; i++)
            _map[i][1][1] = _map[i][2][1] = _map[i][2][2] = _map[i][1][2] = '*';
        
        _map[0][1][1] = '.';
        _map[1][1][2] = '.';
        _map[2][2][1] = '.';
        _map[3][2][2] = '.';
        
        vec<vec<char>> _list(r+2, vec<char>(c+2, '.'));
        for (int i = 1; i <= r; i++)
            for (int k = 1; k <= c; k++)
                cin >> _list[i][k];
        
        
        for (int i = 0; i <= r-2; i++) {
            for (int k = 0; k <= c-2; k++) {
                for (int j = 0; j < 4; j++) {
                    int skipY = (j == 0 or j == 2) ? 0 : 3;
                    int skipX = (j == 0 or j == 1) ? 0 : 3;
                    // cout << j << ' ' << skipX << ' ' << skipY << endl;
                    bool good = true;
                    for (int pi = 0; pi < 4; pi++) {
                        for (int pk = 0; pk < 4; pk++) {
                            if (skipX == pi and skipY == pk) continue;
                            
                            if (_list[i+pi][k+pk] != _map[j][pi][pk]) {
                                good = false;
                                break;
                            }
                        }
                    }
                    
                    if (good) {
                        // cout << "good!" << endl;
                        for (int pi = 1; pi <= 2; pi++)
                            for (int pk = 1; pk <= 2; pk++)
                                if (_map[j][pi][pk] == '*')
                                    _list[i+pi][k+pk] = '.';
                    }
                }
            }
        } 
        
        bool good_ans = true;
        for (int i = 1; i <= r; i++) 
            for (int k = 1; k <= c; k++)
                if (_list[i][k] == '*')
                    good_ans = false;
        
        cout << (good_ans ? "YES" : "NO") << endl;
        
        // devec2(_list);
    }
}