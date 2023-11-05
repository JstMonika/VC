#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using Prior = priority_queue<T>;
template<typename T> using prior = priority_queue<T, vector<T>, greater<T>>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define REP(i, n) for(int i = 0; i < n; i++)
#define REP1(i, n) for(int i = 1; i <= n; i++)
#define eb emplace_back
#define pb push_back
#define mp(a, b) make_pair(a, b)
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }

const int INF = 1e9;
const int nINF = -1e9;
const ll llINF = 4*1e18;
const int MOD = 1e9+7;

ll& pmod(ll& a, ll b) { a = (a+b) % MOD; return a; }
ll& pmod(ll& a, ll b, ll c) { a = (a+b) % c; return a; }
ll& mmod(ll& a, ll b) { a = (a-b+MOD) % MOD; return a; }
ll& mmod(ll& a, ll b, ll c) { a = (a-b+c) % c; return a; }
ll& tmod(ll& a, ll b) { a = (a*b) % MOD; return a; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll mul(ll a, ll b, ll c) { return (a*b) % c; }
ll mPOW(ll a, ll b) { ll res=1; do { if(b%2) tmod(res,a); tmod(a,a); } while (b>>=1); return res; }
ll nPOW(ll a, ll b) { ll res=1; do { if(b%2) res*=a; a*=a; } while (b>>=1); return res; }
ll mFAC(ll a) { ll res = 1; REP1(i, a) tmod(res, i); return res; }
ll nFAC(ll a) { ll res = 1; REP1(i, a) res*=i; return res; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

bool good = false;
vec<int> op(10);

int exec(vec<string>& num, int now) {
    if (num.size() == 1) return -1;
    
    deque<string> s;
    
    for (int i = 0; i < num.size(); i++) {
        if (num[i] == "*") {
            i++;
            ll back = 1ll * stoi(s.back()) * stoi(num[i]);
            
            s.back() = to_string(back);
        } else s.push_back(num[i]);
    }
    
    while (s.size() != 1) {
        string z = s[0], t = s[2];
        
        switch (s[1][0]) {
            case '+':
                s[2] = to_string(stoi(s[0]) + stoi(s[2]));
                break;
            case '-':
                s[2] = to_string(stoi(s[0]) - stoi(s[2]));
                break;
        }
        
        s.pop_front();
        s.pop_front();
    }
    
    return stoi(s[0]);
}

void cal(vec<char>& src, vec<int>& op) {
    
    // devec(src);
    // devec(op);
    // cout << flush;
    
    //*  0: empty, 1: add, 2: sub, 3: mul
    vec<string> ans;
    
    int now = 0;
    for (int i = 0; i < src.size()-1; i++) {
        if (op[i] != 0) {
            // combine from src[now] to src[i].
            string num;
            
            for (int k = now; k <= i; k++)
                num += src[k];
            
            // cout << num << endl << flush;
            ans.eb(num);
            
            switch (op[i]) {
                case 1:
                    ans.eb("+");
                    break;
                case 2:
                    ans.eb("-");
                    break;
                case 3:
                    ans.eb("*");
                    break;
            }
            
            now = i+1;
        }
    }
    
    string num;
    for (int k = now; k < src.size(); k++)
        num += src[k];
    ans.eb(num);
    
    for (int i = 0; i < ans.size(); i++) {
        if (ans[i][0] == '0' && ans[i].size() != 1)
            return;
    }
    
    // devec(ans);
    
    if (exec(ans, 0) == 2000) {
        good = true;
        
        cout << "  ";
        for (auto i : ans)
            cout << i;
        cout << "=\n";
    }
    
    return;
}

void dfs(vec<char>& src, int now) {
    if (now == src.size()-1) {
        cal(src, op);
        
        return;
    }
    
    for (int i = 0; i < 4; i++) {
        op[now] = i;
        dfs(src, now+1);
    }
}

int main()
{
    yccc;
    
    string str;
    int c = 1;
    while (cin >> str) {
        good = false;
        if (str == "=")
            break;
            
        vec<char> _list(str.size()-1);
        
        for (int i = 0; i < str.size()-1; i++) {
            _list[i] = str[i];
        }
        
        cout << "Problem " << c++ << endl;
        
        dfs(_list, 0);
        
        if (!good)
            cout << "  IMPOSSIBLE\n";
    }
}