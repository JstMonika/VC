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

vec<vec<int>> result(2000, vec<int>(2000));

char Alice;

int main()
{
    yccc;
    
    int c;
    cin >> c;
    
    while (c--) {
        string str;
        cin >> str;
        
        for (auto &i : result)
            for (auto &k : i)
                k = -2;
        
        for (int len = 2; len <= str.size(); len += 2) {
            for (int i = 0; i + len - 1 < str.size(); i++) {
                if (len == 2) {
                    result[i][i+len-1] = (str[i] == str[i+len-1] ? 0 : 1);
                } else {
                    bool draw = false;
                    
                    int A[4] = {i, i, i+len-1, i+len-1};
                    int B[4] = {i+1, i+len-1, i, i+len-2};
                    int res[4];
                    
                    for (int z = 0; z < 4; z++) {
                        if (z == 0)
                            res[z] = result[i+2][i+len-1];
                        else if (z == 1 or z == 2)
                            res[z] = result[i+1][i+len-2];
                        else if (z == 2)
                            res[z] = result[i+1][i+len-2];
                        else
                            res[z] = result[i][i+len-3];
                        
                        if (res[z] == 0) {
                            if (str[A[z]] < str[B[z]])
                                res[z] = 1;
                            else if (str[A[z]] == str[B[z]]) {
                                res[z] = 0;
                            } else {
                                res[z] = -1;
                            }
                        }
                    }
                    
                    result[i][i+len-1] = max(min(res[0], res[1]), min(res[2], res[3]));
                }
            }
        }
        
        if (result[0][str.size()-1] == 1)
            cout << "Alice\n";
        else if (result[0][str.size()-1] == 0)
            cout << "Draw\n";
        else
            cout << "Bob\n";
            
        // for (int i = 0; i < str.size(); i++)
        //     for (int k = 0; k < str.size(); k++)
        //         cout << result[i][k] << " \n"[k == str.size()-1];
    }
}