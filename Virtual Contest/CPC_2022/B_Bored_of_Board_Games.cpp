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
    
    int c;
    cin >> c;
    
    while (c--) {
        int R, C;
        cin >> R >> C;
        
        vec<int> row(R), col(C);
        vec<vec<int>> _list(R, vec<int>(C));
        for (int i = 0; i < R; i++) {
            for (int k = 0; k < C; k++) {
                cin >> _list[i][k];
                
                row[i] += _list[i][k];
                col[k] += _list[i][k];
            }
        }
            
        int rCount = 0, cCount = 0;
        for (auto i : row)
            if (i >= 0) rCount++;
        for (auto i : col)
            if (i >= 0) cCount++;
        
        // devec(row);
        // devec(col);
        // debug(rCount);
        // debug(cCount);
        
        deq<bool> flipR(R), flipC(C);
        int idx = 0;
        while ((rCount != R or cCount != C) and idx < 50) {
            for (int i = 0; i < R; i++) {
                if (row[i] < 0) {
                    row[i] *= -1;
                    flipR[i] = !flipR[i];
                    
                    rCount++;
                    
                    for (int k = 0; k < C; k++) {
                        if (col[k] * (col[k] - _list[i][k] * 2) < 0) cCount += (col[k] > 0 ? -1 : 1);
                        col[k] -= _list[i][k] * 2;
                    }
                }
            }
            
            // devec(flipR);
            // devec(col);
            
            // debug(rCount);
            // debug(cCount);
            
            for (int i = 0; i < C; i++) {
                if (col[i] < 0) {
                    col[i] *= -1;
                    flipC[i] = !flipC[i];
                    
                    cCount++;
                    
                    for (int k = 0; k < R; k++) {
                        if (row[k] * (row[k] - _list[k][i] * 2) < 0) rCount += (row[k] > 0 ? -1 : 1);
                        row[k] -= _list[k][i] * 2;
                    }
                }
            }
            
            idx++;
        }
        
        // devec(flipR);
        // devec(flipC);
        // debug(idx);
        
        
        if (idx == 50)
            cout << "No\n";
        else {
            cout << "Yes\n";
            
            vec<int> ansR, ansC;
            for (int i = 0; i < R; i++) if (flipR[i]) ansR.eb(i);
            for (int i = 0; i < C; i++) if (flipC[i]) ansC.eb(i);
            
            cout << ansR.size() << endl;
            for (int i = 0; i < ansR.size(); i++)
                cout << ansR[i]+1 << " \n"[i == ansR.size()-1];
            
            if (ansR.empty()) cout << endl;
            
            cout << ansC.size() << endl;
            for (int i = 0; i < ansC.size(); i++)
                cout << ansC[i]+1 << " \n"[i == ansC.size()-1];
                
            if (ansC.empty()) cout << endl;
        }
    }
}