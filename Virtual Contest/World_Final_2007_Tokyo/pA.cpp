#include <bits/stdc++.h>
using namespace std;

using ll = long long;
// template<typename T> using p = pair<T, T>;
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

int main()
{
    yccc;
    
    int c = 1;
    string s;
    vector<string> p(2);
    while (cin >> p[0] >> p[1] >> s) {
        if (p[0] == "E") break;
        // cout << p[0] << ' ' << p[1] << ' ' << s << endl;
        
        
        if (s == "?") {
            vec<string> type(2);
            int positive[2], pret;
            for (int i = 0; i < 2; i++) {
                type[i] = (p[i].size() == 3 ? p[i].substr(0, 2) : p[i].substr(0, 1));
                positive[i] = p[i].back() == '+';
            }
            
            if (positive[0] + positive[1] == 0) pret = 1;
            else pret = 2;
            
            // cout << pret << endl;
            
            if (type[0].size() > type[1].size()) swap(type[0], type[1]);
            if (type[0].size() == type[1].size() and type[0][0] > type[1][0]) swap(type[0], type[1]);
            
            map<string, int> _map;
            _map["A"] = 1;
            _map["B"] = 2;
            _map["O"] = 3;
            _map["AB"] = 4;
            
            int ret = _map[type[0]] * 10 + _map[type[1]];
            
            if ((ret / 10) > (ret % 10))
                debug(ret);
                
            vec<string> ans;
            
            switch (ret) {
                case 11:
                    ans = {"A", "O"};
                    break;
                case 12:
                    ans = {"A", "B", "O", "AB"};
                    break;
                case 13:
                    ans = {"A", "O"};
                    break;
                case 14:
                    ans = {"A", "B", "AB"};
                    break;
                case 22:
                    ans = {"B", "O"};
                    break;
                case 23:
                    ans = {"B", "O"};
                    break;
                case 24:
                    ans = {"A", "B", "AB"};
                    break;
                case 33:
                    ans = {"O"};
                    break;
                case 34:
                    ans = {"A", "B"};
                    break;
                case 44:
                    ans = {"A", "B", "AB"};
                    break;
            }
            
            cout << "Case " << c++ << ": " << p[0] << ' ' << p[1] << ' ';
            if (ans.size() * pret != 1) cout << "{";
                for (int i = 0; i < pret; i++) {
                    for (int k = 0; k < ans.size(); k++) {
                        if (i+k != 0) cout << ", ";
                        
                        cout << ans[k] << (i == 0 ? '-' : '+');
                    }
                }
            if (ans.size() * pret != 1) cout << "}";
            
            cout << endl;
        } else {
            bool swapped = (p[1] == "?");
            
            if (p[1] == "?")
                swap(p[0], p[1]);
                
            //* p[0] is question.
            vec<string> real_ans;
            for (int i = 1; i <= 4; i++) {
                switch (i) {
                    case 1:
                        p[0] = "A";
                        break;
                    case 2:
                        p[0] = "B";
                        break;
                    case 3:
                        p[0] = "O";
                        break;
                    case 4:
                        p[0] = "AB";
                        break;
                }
                
                auto tmp = p;
                tmp[1] = (tmp[1].size() == 3 ? tmp[1].substr(0, 2) : tmp[1].substr(0, 1));
                
                // devec(tmp);
                if (tmp[0].size() > tmp[1].size()) swap(tmp[0], tmp[1]);
                if (tmp[0].size() == tmp[1].size() and tmp[0][0] > tmp[1][0]) swap(tmp[0], tmp[1]);
                // devec(tmp);
                // devec(tmp);
                
                map<string, int> _map;
                _map["A"] = 1;
                _map["B"] = 2;
                _map["O"] = 3;
                _map["AB"] = 4;
            
                int ret = _map[tmp[0]] * 10 + _map[tmp[1]];
                if ((ret / 10) > (ret % 10))
                    debug(ret);
                    
                // cout << ret << endl;
                vec<string> ans;
                switch (ret) {
                    case 11:
                        ans = {"A", "O"};
                        break;
                    case 12:
                        ans = {"A", "B", "O", "AB"};
                        break;
                    case 13:
                        ans = {"A", "O"};
                        break;
                    case 14:
                        ans = {"A", "B", "AB"};
                        break;
                    case 22:
                        ans = {"B", "O"};
                        break;
                    case 23:
                        ans = {"B", "O"};
                        break;
                    case 24:
                        ans = {"A", "B", "AB"};
                        break;
                    case 33:
                        ans = {"O"};
                        break;
                    case 34:
                        ans = {"A", "B"};
                        break;
                    case 44:
                        ans = {"A", "B", "AB"};
                        break;
                } 
                
                auto stmp = s.substr(0, (s.size() == 3 ? 2 : 1));
                
                
                if (any_of(al(ans), [stmp](string src){ return src == stmp; }))
                    switch (i) {
                        case 1:
                            real_ans.eb("A");
                            break;
                        case 2:
                            real_ans.eb("B");
                            break;
                        case 3:
                            real_ans.eb("O");
                            break;
                        case 4:
                            real_ans.eb("AB");
                            break;
                    }
            }
                
            int pos = 2;
            if (p[1].back() == '-' and s.back() == '+') pos = 1;
            // cout << pos << endl;
            
            cout << "Case " << c++ << ": ";
            
            if (swapped) cout << p[1] << ' ';
            
            if (real_ans.size() * pos > 1) cout << "{";
                for (int i = 0; i < pos; i++) {
                    for (int k = 0; k < real_ans.size(); k++) {
                        if (i+k != 0) cout << ", ";
                        
                        cout << real_ans[k] << (i == 0 ? '+' : '-');
                    }
                }
            if (real_ans.size() * pos > 1) cout << "}";
            
            if (real_ans.size() * pos == 0) cout << "IMPOSSIBLE";
            
            if (!swapped) cout << ' ' << p[1];
            cout << ' ' << s << endl;
        }
    }
}