#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

// #define dbg

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

#ifndef dbg
#define endl '\n'
#define debug(x) ;
#define devec(v) ;
#define devec2(v) ;
#else
#define debug(x) cout << " > " << #x << ": " << x << endl;
#define devec(v) cout << " > " << #v << ": "; for (auto i : v) cout << i << ' '; cout << endl;
#define devec2(v) cout << " > " << #v << ":\n"; for (auto i : v) { for (auto k : i) cout << ' ' << k; cout << endl; }
#endif

const int INF = 1e9;
const ll llINF = 1e18;
const int MOD = 1e9+7;
const double eps = 1e-6;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-6) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

struct Gate {
    char type;
    vec<string> s;
    int inEdge;
    bool exist;
    
    Gate() {
        inEdge = 0;
        exist = false;
    }
};

deq<bool> input(100), G_result(100), output(100);

bool result(Gate src, deq<bool> arr) {
    deq<bool> val;
    for (auto i : src.s) {
        int tmp = stoi(i.substr(1));
        
        if (i[0] == 'i')
            tmp = input[tmp-1];
        else
            tmp = G_result[tmp-1];
        
        val.eb(tmp);
    }
    
    switch (src.type) {
        case 'n':
            return !val[0];
        case 'a':
            return val[0] & val[1];
        case 'o':
            return val[0] | val[1];
        case 'x':
            return val[0] ^ val[1];
    }
}

int main()
{
    yccc;
    
    int in, n, out, c = 1;
    while (cin >> in >> n >> out) {
        if (!in) break;
        
        vec<Gate> gate(n);
        vec<int> que;
        
        for (int i = 0; i < n; i++) {
            string tmp;
            cin >> gate[i].type >> tmp;
            
            gate[i].s.eb(tmp);
            gate[i].inEdge += (tmp[0] == 'g');
            
            if (gate[i].type != 'n') {
                cin >> tmp;
                gate[i].s.eb(tmp);
                gate[i].inEdge += (tmp[0] == 'g');
            }
        }
        
        // cout << "inEdge\n";
        // for (int i = 0; i < n; i++) {
        //     cout << gate[i].inEdge << ' ';
        // }
        // cout << endl;
        
        while (que.size() != n) {
            for (int i = 0; i < n; i++) {
                // cout << gate[i].inEdge << ' ';
                if (gate[i].exist) continue;
                
                if (gate[i].inEdge == 0) {
                    que.eb(i);
                    
                    for (int k = 0; k < n; k++) {
                        for (auto z : gate[k].s) {
                            if (z[0] == 'g' and stoi(z.substr(1))-1 == i)
                                gate[k].inEdge--;
                        }
                    }
                    
                    gate[i].exist = true;
                }
            }
            
            // cout << endl;
        }
        vec<int> link(out);
        for (auto &i : link)
            cin >> i;
         
        // cout << "que\n";   
        // for (auto i : que) {
        //     cout << i << ' ';
        // }
        // cout << endl;
            
        input.resize(in);
        output.resize(out);
        
        int q;
        cin >> q;
        set<p<int>> ans;
        for (int nq = 0; nq < q; nq++) {
            for (int i = 0; i < in; i++) {
                cin >> input[i];
            }
            for (int i = 0; i < out; i++) {
                cin >> output[i];
            }
            set<p<int>> tmp_ans;
            
            for (int i = -1; i < n; i++) {
                for (int z = 0; z < 3; z++) {
                    if (z > 0 and i == -1)
                        break;
                    
                    for (auto k : que) {
                        G_result[k] = result(gate[k], G_result);
                        
                        if (i == k) {
                            if (z == 2)
                                G_result[k] = !G_result[k];
                            else
                                G_result[k] = z;
                        }
                    }
                    
                    int tmp;
                    bool good = true;
                    for (int k = 0; k < out; k++) {
                        if (G_result[link[k]-1] != output[k])
                            good = false;
                    }
                    
                    if (good) {
                        if (!nq)
                            ans.emplace(i, z);
                        else
                            tmp_ans.emplace(i, z);
                    }
                }
            }
            
            // for (auto i : tmp_ans)
            //     cout << i << endl;
            // cout << ">======\n";
            
            if (nq) {   
                set<p<int>> next_ans;
                for (auto i : ans) {
                    if (tmp_ans.find(i) != tmp_ans.end())
                        next_ans.emplace(i);
                }
                
                ans = next_ans;
            }
                
            // for (auto i : ans)
            //     cout << i << endl;
            // cout << "-----\n";
            
            // for (int i = 0; i < in; i++)
            //     cout << input[i] << ' ';
            // cout << endl;
        }
        
        cout << "Case " << c++ << ": ";
        
        if ((*ans.begin()).F == -1) {
            cout << "No faults detected\n";
        } else if (ans.size() >= 2) {
            cout << "Unable to totally classify the failure\n";
        } else {
            cout << "Gate " << (*ans.begin()).F+1 << " is failing; ";
            cout << "output ";
            
            if ((*ans.begin()).S == 0)
                cout << "stuck at 0\n";
            else if ((*ans.begin()).S == 1)
                cout << "stuck at 1\n";
            else
                cout << "inverted\n";
        }
    }
}