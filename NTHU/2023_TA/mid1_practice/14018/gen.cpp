#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using p = pair<T, T>;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int r(int s, int e) {
    return rnd() % (e-s+1) + s;
}

int main() {
    yccc;
	
    vec<string> _list;
    
    for (int i = 0; i < 26; i++) {
        _list.eb(string(1, 'a' + i));
        _list.eb(string(1, 'A' + i));
    }
    for (int i = 0; i < 10; i++)
        _list.eb("\'" + string(1, '0' + i) + "\'");
    
    int c = r(70, 100);
    
    assert(c >= 1 and c <= 100);
    
    for (int i = 0; i < c; i++) {
        int n = r(50, 280);
     
        string str;
        for (int z = 0; z < n; z++) {
            int num = r(1, 100);
            assert(num <= 100 and num >= 0);
            
            str += to_string(num) + _list[r(0, _list.size()-1)];
        }
        
        assert(str.size() >= 1 and str.size() <= 1000);
        cout << str << endl;
    }   
}
