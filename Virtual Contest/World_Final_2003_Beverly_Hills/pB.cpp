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

vec<deque<bool>> _list(2);

void convert(vec<string> src) {
    for (int i = 0; i < 2; i++) {
        vec<int> num(src[i].size());
        for (int k = 0; k < src[i].size(); k++)
            num[k] = src[i][k] - '0';
            
        _list[i].clear();
        
        while (any_of(al(num), [](int m){ return m != 0; })) {
            _list[i].eb(num[src[i].size()-1] % 2);
            
            for (int k = 0; k < src[i].size(); k++) {
                if (k != src[i].size() - 1 and num[k] % 2)
                    num[k+1] += 10;
                num[k] /= 2;
            }
        }
    }
    
    if (_list[0].size() < _list[1].size())
        _list[0].resize(_list[1].size());
    else
        _list[1].resize(_list[0].size());
}

string number(deque<bool>& src) {
    vec<int> ret(600);
    
    for (int i = src.size()-1; i >= 0; i--) {
        for (int k = 0; k < 600; k++) {
            ret[k] *= 2;
        }
        
        if (src[i] == 1)
            ret[0]++;
        
        for (int k = 0; k < 600; k++) {
            if (k != 599) {
                ret[k+1] += ret[k] / 10;
                ret[k] %= 10;
            }
        }
        
        // devec(ret);
    }
    
    bool first = false;
    
    string sret;
    for (int i = 599; i >= 0; i--) {
        if (first)
            sret += to_string(ret[i]);
        else if (ret[i] != 0) {
            sret += to_string(ret[i]);
            first = true;
        }
    }
    
    if (sret.size() == 0) sret = "0";
    
    return sret;
}

int main()
{
    yccc;
    
    int c = 1;
    vec<string> s(2);
    
    while (cin >> s[0] >> s[1]) {
        if (s[0] == "0" and s[1] == "0") break;
        convert(s);
        
        // devec(_list[0]);
        // devec(_list[1]);
        
        int n = _list[0].size();
        
        bool good = false;
        deque<bool> _ans(_list[0].size());
        for (int i = 0; i < 2; i++) {
            fill(al(_ans), 0);
            auto tmp = _list[0];
            
            if (i) {
                _ans[n-1] = !_ans[n-1];
                tmp[n-1] = !tmp[n-1];
                
                if (n-2 >= 0)
                    tmp[n-2] = !tmp[n-2];
            }
            
            for (int k = n-2; k >= 0; k--) {
                if (tmp[k+1] != _list[1][k+1]) {
                    _ans[k] = !_ans[k];
                    
                    for (int m = k+1; m >= k-1 and m >= 0; m--)
                        tmp[m] = !tmp[m];
                }
            }
            
            if (tmp[0] == _list[1][0]) {
                // devec(_ans);
                good = true;
                break;
            }
        }
        
        if (c >= 2)
            cout << endl;
        
        cout << "Case Number " << c++ << ": ";
        
        if (good)
            cout << number(_ans) << endl;
        else
            cout << "impossible\n";
    }
}