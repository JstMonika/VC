#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
// #define endl '\n'
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

string str;
deque<bool> exist;
int m, n;

int find(int idx, int next) {
    while (next) {
        (idx += 1) %= m;
        
        if (exist[idx] == false)
            next--;
    }
    
    exist[idx] = true;
    return idx;
}

bool check(string goal, string src) {
    // cout << "here?" << endl;
    int g[26] = {0}, s[26] = {0};
    
    for (auto i : goal)
        g[i - 'A']++;
    for (auto i : src)
        s[i - 'A']++;
        
    for (int i = 0; i < 26; i++)
        if (g[i] * 2 > s[i])
            return false;
            
    return true;
}

int first(int next, char ch) {
    while (exist[next])
        (next += 1) %= m;
    
    if (str[next] != ch)
        return -1;
    
    exist[next] = true;
    return next;
}

int main()
{
    yccc;
    
    int c = 1;
    while (cin >> str) {
        if (str == "X")
            break;
        
        m = str.size();
        
        exist.resize(m);
        fill(al(exist), false);
        
        set<string> ans;
        
        for (n = m/2; n >= 1; n--) {
            ans.clear();
            
            for (int s = 0; s < m; s++) {
                for (int i = 0; i < m; i++) {
                    fill(al(exist), false);
                    
                    int count = n, idx = s;
                    string goal(n, 0);
                    goal[0] = str[s];
                    exist[s] = true;
                    
                    // cout << s << ' ' << i << endl;
                    for (int z = 1; z < n; z++) {
                        idx = find(idx, i+1);
                        goal[z] = str[idx];
                        
                        // devec(exist);
                    }
                    
                    // cout << goal << endl;
                    
                    if (!check(goal, str)) {
                        // cout << "bad" << endl;
                        continue;
                    }
                    // cout << "check good" << endl;
                    
                    auto backup = exist;
                    
                    for (int t = 0; t < m; t++) {
                        exist = backup;
                        
                        //* modify it.
                        int idx = -1, r_idx;
                        if ((r_idx = idx = first(t, goal[0])) == -1) {
                            continue;
                        }
                        // cout << "good when t = " << t << endl;
                        // devec(exist);
                        
                        auto first_done = exist;
                        for (int j = 0; j < m; j++) {
                            //* restore exist initial.
                            exist = first_done;
                            idx = r_idx;
                            
                            bool good = true;
                            // cout << j << ": ";
                            for (int z = 1; z < n; z++) {
                                // cout << idx << ' ' << j+1 << endl;
                                idx = find(idx, j+1);
                                // cout << idx << ' ';
                                
                                if (goal[z] != str[idx]) {
                                    good = false;
                                    break;
                                    // cout << endl;
                                }
                            }
                            
                            // cout << endl;
                            
                            if (good) {
                                // cout << "finish when j = " << j << endl;
                                //* push ans.
                                ans.emplace(goal);
                            }
                        }
                    }
                }
            }
            
            if (ans.size() == 1) {
                //* single answer.
                
                cout << "Code " << c++ << ": " << *ans.begin() << endl;
                
                break;
            } else if (ans.size() >= 2) {
                //* ambiguous.
                
                cout << "Code " << c++ << ": Codeword not unique\n"; 
                
                break;
            } 
        }
        
    }
}