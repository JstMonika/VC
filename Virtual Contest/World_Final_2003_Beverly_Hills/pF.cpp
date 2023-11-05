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

int idx[2];
string str[2], ans;

void convert(string& s) {
    string tmp;
    
    for (auto i : s) {
        switch (i) {
            case '0':
                tmp += "0000";
                break;
            case '1':
                tmp += "0001";
                break;    
            case '2':
                tmp += "0010";
                break;    
            case '3':
                tmp += "0011";
                break;    
            case '4':
                tmp += "0100";
                break;    
            case '5':
                tmp += "0101";
                break;    
            case '6':
                tmp += "0110";
                break;    
            case '7':
                tmp += "0111";
                break;    
            case '8':
                tmp += "1000";
                break;    
            case '9':
                tmp += "1001";
                break;    
            case 'A':
                tmp += "1010";
                break;    
            case 'B':
                tmp += "1011";
                break;    
            case 'C':
                tmp += "1100";
                break;    
            case 'D':
                tmp += "1101";
                break;    
            case 'E':
                tmp += "1110";
                break;    
            case 'F':
                tmp += "1111";
                break;    
        }
    }
    
    s = tmp;
}

map<string, char> _map;
string rconvert(string s) {
    s = string((4-((s.size()+1) % 4)) % 4, '0') + "1" + s;
    
    string tmp;
    for (int i = 0; i < s.size(); i += 4) {
        tmp += _map[s.substr(i, 4)];
    }
    
    return tmp;
}

void r(int i) {
    if (str[i][idx[i]] == '1') {
        idx[i] += 2;
        return;
    } else {
        idx[i]++;
        
        for (int k = 0; k < 4; k++) r(i);
    }
}

string recur() {
    // for (int i = 0; i < 2; i++) {
    //     cout << str[i] << endl;
    //     cout << string(idx[i], ' ') << "^\n";
    // }
    
    if (str[0][idx[0]] == '1') {
        r(0);
        int prev = idx[1];
        r(1);
        
        return (str[0][idx[0]-1] == '1' ? str[1].substr(prev, (idx[1]-prev)) : "10");
    } else if (str[1][idx[1]] == '1') {
        int prev = idx[0];
        r(0);
        r(1);
        
        return (str[1][idx[1]-1] == '1' ? str[0].substr(prev, (idx[0]-prev)) : "10");
    } else {
        idx[0]++;
        idx[1]++;
        
        vec<string> s(4);
        for (int i = 0; i < 4; i++) {
            s[i] = recur();
        }
        
        if (all_of(al(s), [](string src) { return src == "10"; })) {
            // cout << "ret 10\n";
            return "10";
        } else if (all_of(al(s), [](string src) { return src == "11"; })) {
            // cout << "ret 11\n";
            return "11";
        }
        
        // cout << "ret " << ("0" + s[0] + s[1] + s[2] + s[3]) << endl;
        return ("0" + s[0] + s[1] + s[2] + s[3]);
    }
}

int main()
{
    yccc;
    
    _map["0000"] = '0';
    _map["0001"] = '1';
    _map["0010"] = '2';
    _map["0011"] = '3';
    _map["0100"] = '4';
    _map["0101"] = '5';
    _map["0110"] = '6';
    _map["0111"] = '7';
    _map["1000"] = '8';
    _map["1001"] = '9';
    _map["1010"] = 'A';
    _map["1011"] = 'B';
    _map["1100"] = 'C';
    _map["1101"] = 'D';
    _map["1110"] = 'E';
    _map["1111"] = 'F';
    
    int c = 1;
    while (cin >> str[0] >> str[1]) {
        if (str[0] == "0") break;
        
        if (c != 1) cout << endl;
        
        for (int i = 0; i < 2; i++) {
            convert(str[i]);
            
            for (idx[i] = 1; str[i][idx[i]-1] == '0'; idx[i]++);
        }
        
        cout << "Image " << c++ << ":\n" << rconvert(recur()) << endl;
    }
}