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
const double eps = 1e-9;
const double PI = acos(-1);

double fcmp(double a, double b, double eps = 1e-9) {
    if (fabs(a-b) < eps) return 0;
    return a - b;
}

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2>& a) { in >> a.F >> a.S; return in; }

template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) { out << a.F << ' ' << a.S; return out; }

string str;

struct term {
    int type;
    deq<int> A;
    vec<vec<int>> B;
    vec<vec<vec<int>>> C;
};

void next(int& i, int n) {
    ++i %= n; 
}

term parsing() {
    while (cin.peek() == ' ') cin.get();
    if (cin.peek() == '\n') return term();
    
    int num;
    string tmp;
    char ch = cin.peek();
    
    if (ch == '(') {
        cin >> ch; //* remove (
        auto ret = parsing();
        cin >> ch; //* remove )
        
        return ret;
    } else if (isdigit(ch)) {
        vec<int> vf;
        while (isdigit(cin.peek())) {
            cin >> num;
            vf.eb(num);
            
            cin.get();
        }
        
        if (cin.peek() == 'r') { //* rho
            cin >> tmp;
            
            auto vs = parsing();
            term ret;
            
            ret.type = vf.size();
            switch (vf.size()) {
                case 1:
                    ret.A.resize(vf[0]);
                    
                    int idx = 0, n = vs.A.size();
                    for (auto i : ret.A) {
                        i = vs.A[idx];
                        next(idx, n);
                    }
                    
                    break;
                case 2:
                    ret.B.resize(vf[0]);
                    
                    int idx = 0, n = vs.A.size();
                    for (auto i : ret.B) {
                        i.resize(vf[1]);
                        
                        for (auto k : i) {
                            k = vs.A[idx];
                            next(idx, n);
                        }
                    }
                    
                    break;
                case 3:
                    ret.C.resize(vf[0]);
                    
                    int idx = 0, n = vs.A.size();
                    for (auto i : ret.C) {
                        i.resize(vf[1]);
                        
                        for (auto k : i) {
                            k.resize(vf[2]);
                            
                            for (auto r : k) {
                                r = vs.A[idx];
                                next(idx, n);
                            }
                        }
                    }
            }
            
            return ret;
        } else if (cin.peek() == 'd') { //* drop
            cin >> tmp;
            
            auto vs = parsing();
            
            for (int i = 0; i < vf[0]; i++)
                vs.A.pop_front();
            
            return vs;
        }
        
        
    } else if (isalpha(ch)) {
        
    } else {
        
    }
}

int main()
{
    yccc;
    
    while (true) {
        if (cin.peek() == '#') break;
        
        parsing();
    }
}