#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

int _list[9][9];
bool row[10][10], column[10][10], block[10][10];

string ans(81, '0');

int f(int i, int k) {
    return (i / 3 * 3) + (k / 3);
}

bool go(int i, int k) {
    if (k == 9) k = 0, i += 1;
    
    if (i == 9) {
        for (int I = 0; I < 9; I++) {
            for (int K = 0; K < 9; K++) {
                cout << _list[I][K];
            }
        }
        
        return true;
    }
    
    if (_list[i][k] != -1) {
        if (go(i, k+1)) return true;
    }
    else {
        for (int r = 1; r <= 9; r++) {
            if (row[i][r]) continue;
            if (column[k][r]) continue;
            if (block[f(i, k)][r]) continue;
            
            _list[i][k] = r;
            row[i][r] = true;
            column[k][r] = true;
            block[f(i, k)][r] = true;
            if (go(i, k+1)) return true;
            row[i][r] = false;
            column[k][r] = false;
            block[f(i, k)][r] = false;
            _list[i][k] = -1;
        }
    }
    
    return false;
}


int main() {
    yccc;
    
    int c = 0;
    string str;
    while (cin >> str) {
        if (str == "end") break;
        if (c) cout << endl;
        c++;
        
        // reverse(al(str));
        
        for (int i = 0; i <= 9; i++) {
            for (int k = 0; k <= 9; k++) {
                row[i][k] = column[i][k] = block[i][k] = false;
            }
        }
        bool good = true;
        for (int i = 0; i < 9; i++) {
            for (int k = 0; k < 9; k++) {
                int num = (str[i*9+k] == '.' ? -1 : str[i*9+k] - '0');
                
                _list[i][k] = num;
                if (num != -1) {
                    if (row[i][num]) good = false;
                    else row[i][num] = true;
                    
                    if (column[k][num]) good = false;
                    column[k][num] = true;
                    
                    if (block[f(i, k)][num]) good = false;
                    block[f(i, k)][num] = true;
                }
            }
        }
        
        if (good and go(0, 0)) {
            // reverse(al(ans));
        } else {
            cout << "No solution.";
        }
    }
}