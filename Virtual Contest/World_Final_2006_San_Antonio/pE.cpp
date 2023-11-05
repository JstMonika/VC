#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#ifndef dbg
#define endl '\n'
#endif

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

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
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int oL, oN, ret;
string str;
int gCount, lCount;

void go(int now) {
    // cout << now << endl;
    //* base
    if (now == str.size()) {
        // cout << gCount << ' ' << lCount << endl;
        if (gCount == oN and gCount + lCount == oL)
            ret++;
        
        return;
    }
    
    if ((now == 0 or str[now-1] == '0') and (str[now] == '1')) {
        int num = 1;
        for (int i = 1; now + i < str.size(); i++) {
            num *= 2;
            num += (str[now+i] == '1');
            
            if (now+i+1 < str.size() and str[now+i+1] == '1') continue;
            if (num == 2) continue;
            
            gCount += num;
            lCount += (now+i+1 < str.size());   //* str[now+i+1] == '0'.
            
            int next = (now+i+1 < str.size() ? now+i+2 : now+i+1);
            go(next);
            
            gCount -= num;
            lCount -= (now+i+1 < str.size());
        }
    }
    
    bool good = false;
    for (int i = now; i <= now + 2; i++)
        if (i >= str.size() or str[i] == '0') good = true;
    
    // cout << now << ' ' << str.size() << endl;
    
    if (good) {
        if (str[now] == '0')
            lCount++;
        else
            gCount++;
            
        go(now+1);
        
        if (str[now] == '0')
            lCount--;
        else
            gCount--;
    }
}

int main()
{
    yccc;
    int c = 1;
    while (cin >> oL >> oN) {
        if (oL == 0) break;
        
        cin >> str;
        
        ret = 0;
        gCount = lCount = 0;
        
        cout << "Case #" << c++ << ": ";
        go(0);
        
        if (ret == 0) cout << "NO\n";
        else if (ret >= 2) cout << "NOT UNIQUE\n";
        else cout << "YES\n";
        
        cout << flush;
    }
}