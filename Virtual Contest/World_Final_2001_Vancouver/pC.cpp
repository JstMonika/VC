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

struct Slot {
    int x, y;
    bool down;

    int avail;
    bool used;

    Slot() {}
};

int n;
vec<Slot> slot;
vec<string> str;
deque<bool> used;

set<string> ans;

pair<int, int> p[10][10];

bool valid(int i, int k) {
    //* i: slot idx, k: string idx.
    
    // cout << 0;
    if (used[k])
        return false;

    if (slot[i].down) {
        // cout << 1;
        if (slot[i].x + str[k].size() > 10) {
            return false;
        }
        
        // cout << 2;
        if (slot[i].x-1 >= 0 and p[slot[i].x-1][slot[i].y].F > 0)
            return false;
        // cout << 3;
        if (slot[i].x+str[k].size() < 10 and p[slot[i].x+str[k].size()][slot[i].y].F > 0)
            return false;
    
        // cout << 4;
        for (int m = 0; m < str[k].size(); m++) {
            if (!(p[slot[i].x + m][slot[i].y].F == 0 or p[slot[i].x + m][slot[i].y].F == str[k][m])) {
                return false;
            }
        }

    } else {
        // cout << 1;
        if (slot[i].y + str[k].size() > 10) {
            return false;
        }
        
        // cout << 2;
        if (slot[i].y-1 >= 0 and p[slot[i].x][slot[i].y-1].F > 0)
            return false;
        // cout << 3;
        if (slot[i].y+str[k].size() < 10 and p[slot[i].x][slot[i].y+str[k].size()].F > 0)
            return false;
            
        // cout << 4;
        for (int m = 0; m < str[k].size(); m++) {
            if (!(p[slot[i].x][slot[i].y + m].F == 0 or p[slot[i].x][slot[i].y + m].F == str[k][m])) {
                return false;
            }
        }
    }

    return true;
}

vec<int> seq;
bool find() {
    seq.clear();
    
    vec<pii> s;
    
    for (int i = 0; i < n; i++) {
        if (slot[i].used)
            continue;

        int count = 0;
        for (int k = 0; k < n+1; k++) {
            if (valid(i, k))
                count++;
        }
        
        s.eb(count, i);
    }
    
    sort(al(s));
    
    for (int i = 0; i < s.size(); i++) {
        if (s[i].F > 0)
            seq.eb(s[i].S);
        else
            return false;
    }   
    
    return true;
}

void fillChar(int x, int y, int ch) {
    if (p[x][y].F != ch) {
        p[x][y].F = ch;
        p[x][y].S = 1;
    } else {
        p[x][y].S++;
    }
}

void unfillChar(int x, int y, int ch) {
    if (p[x][y].S == 1) {
        p[x][y].F = 0;
        p[x][y].S = 0;
    } else {
        p[x][y].S--;
    }
}

void fill(int i, int k, bool f) {
    if (f) {
        if (slot[i].down) {
            if (slot[i].x-1 >= 0)
                fillChar(slot[i].x-1, slot[i].y, -1);
            if (slot[i].x+str[k].size() < 10)
                fillChar(slot[i].x+str[k].size(), slot[i].y, -1);

            for (int m = 0; m < str[k].size(); m++) {
                fillChar(slot[i].x+m, slot[i].y, str[k][m]);
            }
        } else {
            if (slot[i].y-1 >= 0)
                fillChar(slot[i].x, slot[i].y-1, -1);
            if (slot[i].y+str[k].size() < 10)
                fillChar(slot[i].x, slot[i].y+str[k].size(), -1);

            for (int m = 0; m < str[k].size(); m++) {
                fillChar(slot[i].x, slot[i].y+m, str[k][m]);
            }
        }
    } else {
        if (slot[i].down) {
            if (slot[i].x-1 >= 0)
                unfillChar(slot[i].x-1, slot[i].y, -1);
            if (slot[i].x+str[k].size() < 10)
                unfillChar(slot[i].x+str[k].size(), slot[i].y, -1);

            for (int m = 0; m < str[k].size(); m++) {
                unfillChar(slot[i].x+m, slot[i].y, str[k][m]);
            }
        } else {
            if (slot[i].y-1 >= 0)
                unfillChar(slot[i].x, slot[i].y-1, -1);
            if (slot[i].y+str[k].size() < 10)
                unfillChar(slot[i].x, slot[i].y+str[k].size(), -1);

            for (int m = 0; m < str[k].size(); m++) {
                unfillChar(slot[i].x, slot[i].y+m, str[k][m]);
            }
        }
    }
}

void dfs(int now, int step) {
    // for (int i = 0; i < 10; i++) {
    //     for (int k = 0; k < 10; k++) {
    //         if (p[i][k].F == -1)
    //             cout << '#';
    //         else if (p[i][k].S == 0)
    //             cout << '@';
    //         else 
    //             cout << char(p[i][k].F);
    //     }

    //     cout << endl;
    // }
    // cout << endl;
    
    for (int k = 0; k < str.size(); k++) {
        // cout << now << ' ' << k << ' ' << valid(now, k) << endl;
        if (valid(now, k)) {
            // cout << "fill " << str[k] << " at slot " << now << endl;
            fill(now, k, true);
            slot[now].used = true;
            used[k] = true;
            
            if (step == n-1) {
                // cout << "here\n";
                for (int i = 0; i < n+1; i++) {
                    if (!used[i])
                        ans.insert(str[i]);
                }
            }
            
            if (!find()) {
                used[k] = false;
                slot[now].used = false;
                fill(now, k, false);
                
                continue;
            }
            
            for (int i = 0; i < seq.size(); i++) {
                // cout << "now focus on slot " << seq[i] << endl;
                dfs(seq[i], step+1);
            }
            
            used[k] = false;
            slot[now].used = false;
            fill(now, k, false);
        }
    }
}

int main() {

    int c = 1;
    while (cin >> n) {
        if (!n)
            break;

        ans.clear();
        memset(p, 0, sizeof(p));

        slot.resize(n);
        used.resize(n+1);
        fill(al(used), false);

        for (int i = 0; i < n; i++) {
            char tmp;
            cin >> slot[i].x >> slot[i].y >> tmp;
            slot[i].x--;
            slot[i].y--;
            slot[i].down = (tmp == 'D');

            slot[i].avail = 0;
            slot[i].used = false;
        }

        str.resize(n+1);
        for (int i = 0; i < n+1; i++) {
            cin >> str[i];
        }
        
        if (find()) {
            for (int i = 0; i < seq.size(); i++)
                dfs(seq[i], 0);
        }
        
        
        cout << "Trial " << c++ << ":";
        
        if (ans.empty())
            cout << " Impossible";
            
        for (auto i : ans) {
            cout << ' ' << i;
        }
        cout << endl << endl;
    }
}