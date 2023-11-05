#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
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
const ll llINF = 2*1e18;
const int MOD = 1e9+7;

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { cout << a.F << ' ' << a.S; return out; }

int next(int i) {
    return (i+1) % 12;
}

int prev(int i) {
    return (i+11) % 12;
}

vec<vec<int>> note = {
    {31, 22},
    {32, 40},
    {41},
    {42, 50},
    {51, 60},
    {61, 52},
    {62, 70},
    {71},
    {72, 10},
    {11},
    {12, 20},
    {21, 30}
};

vec<int> vs, ve;

int convert(string src) {
    
    int ret = 0;

    ret += (src[0] - 'A' + 1) * 10;

    if (src.size() == 2) {
        ret += (src[1] == '#' ? 2 : 0);
    } else ret += 1;

    return ret;
}

string nconvert(int src) {
    string ret;

    ret += char((src / 10) - 1 + 'A');
    if (src % 10 != 1)
        ret += (src % 10 == 0 ? 'b' : '#');

    return ret;
}

bool check(int s, vec<int>& v) {
    int i = 0;
    for (;; i++) {
        bool good = false;
        for (int k = 0; k < note[i].size(); k++)
            if (note[i][k] == s) good = true;

        if (good)
            break;
    }

    bool b = false, u = false;
    int now = s / 10;
    
    // cout << i << endl;
    for (int k = 0; k < 8; k++) {
        bool found = false;

        for (int m = 0; m < note[i].size(); m++) {
            // cout << note[i][m] / 10 << ' ' << now << endl;
            if (note[i][m] / 10 == now) {
                found = true;
                // cout << "emplace " << nconvert(note[i][m]) << "\n";
                v.eb(note[i][m]);

                if (note[i][m] % 10 == 0) {
                    if (u)
                        return false;

                    b = true;
                }
                else if (note[i][m] % 10 == 2) {
                    if (b)
                        return false;

                    u = true;
                }

                break;
            }
        }

        if (!found)
            return false;

        now = (now % 7) + 1;

        i = next(i);
        if (!(k == 2 or k == 6))
            i = next(i);
    }

    return true;
}

int main()
{
    yccc;

    bool first = true;
    string s;
    while (cin >> s) {
        if (s == "*")
            break;
        
        if (first)
            first = false;
        else cout << endl;

        string e;
        cin >> e;

        int ns = convert(s), ne = convert(e);

        vs.clear();
        if (!check(ns, vs)) {
            cout << "Key of " << s << " is not a valid major key\n";
            
            string tmp;

            while (cin >> tmp) {
                if (tmp == "*")
                    break;
            }

            continue;
        }

        ve.clear();
        if (!check(ne, ve)) {
            cout << "Key of " << e << " is not a valid major key\n";

            string tmp;

            while (cin >> tmp) {
                if (tmp == "*")
                    break;
            }

            continue;
        }

        cout << "Transposing from " << s << " to " << e << ":\n";

        string t;
        while (cin >> t) {
            if (t == "*")
                break;

            int vt = convert(t);

            bool good = false;
            for (int i = 0; i < vs.size(); i++) {
                if (vs[i] == vt) {
                    good = true;

                    cout << "  " << t << " transposes to " << nconvert(ve[i]) << "\n";
                    break;
                }
            }

            if (!good)
                cout << "  " << t << " is not a valid note in the " << s << " major scale\n";
        }
    }
}