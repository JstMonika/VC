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

void strgen(string str, int idx) {
    
}

set<set<string>> vis;
set<string> now;
set<string> _set, next_set;
int n;

void gen(string str, int idx, int last) {
    if (idx == 8) {
        now.insert(str);
        return;
    }
    
    if (last) {
        str[idx] = '1';
        gen(str, idx+1, last-1);
        str[idx] = '0';
    }
    
    gen(str, idx+1, last);
}

int main()
{
    yccc;
    
    string next;
    bool first = true;
    int c;
    cin >> c;
    while (true) {
        if (first) {
            cout << "01010101" << endl << flush;
            first = false;
        } else if (n == 4) {
            cout << "10101010" << endl << flush;
        } else {
            cout << next << endl << flush;
        }
        
        cin >> n;
        
        string str = "00000000";
        
        now.clear();
        
        gen(str, 0, n);
        
        
        int best = INF;

        
        for (int i = 1; i < (1 << 8); i++) {
            _set.clear();
            string tmp = "00000000";
            for (int k = 0; k < 8; k++) {
                tmp[k] = ((i & (1 << k)) ? '1' : '0');
            }
            
            for (auto i : now) {
                string x = "00000000";
                
                int count = 0;
                for (int k = 0; k < 8; k++) {
                    x[k] = (i[k] != tmp[k] ? '1' : '0');
                }
                
                _set.insert(x);
            }
            
            if (_set.size() < best and (vis.find(_set) == vis.end())) {
                best = _set.size();
                next = tmp;
                next_set = _set;
            }
        }
        
        vis.insert(next_set);
        
        if (n == 0) {
            c--;
            vis.clear();
            
            if (c == 0)
                break;
        }
        
        if (n == -1)
            break;
    }
}