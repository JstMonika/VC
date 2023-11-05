#include <bits/stdc++.h>
using namespace std;

using ll = long long;
template<typename T> using vec = vector<T>;
template<typename T> using deq = deque<T>;
template<typename T> using p = pair<T, T>;

#define yccc ios_base::sync_with_stdio(false), cin.tie(0)
#define endl '\n'
#define al(a) a.begin(),a.end()
#define F first
#define S second
#define eb emplace_back

vec<vec<bool>> _list;

int main() {
    yccc;
    
    int t;
    cin >> t;
    
    while (t--) {
        int r, c;
        cin >> r >> c;
        
        int total = 0;
        _list.assign(r, vec<bool>(c));
        vec<int> count(r);
        
        char tmp;
        for (int i = 0; i < r; i++)
            for (int k = 0; k < c; k++) {
                cin >> tmp;
                
                _list[i][k] = (tmp == '1');
                count[i] += (tmp == '1');
                total += (tmp == '1');
            }
        
        vec<pair<p<int>, int>> ans;
                
        if (total % r != 0) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < r; i++) {
                int idx = 0;
                while (count[i] < total / r) {
                    while ((count[idx] <= total / r) or i == idx) idx++;
                    
                    bitset<100000> diff = _list[i] ^ _list[idx];
                    
                    for (int k = 0; k < c; k++) {
                        if (diff[k] and !_list[i][k]) {
                            _list[i][k] = 1;
                            _list[idx][k] = 0;
                            
                            count[i]++;
                            count[idx]--;
                            
                            ans.eb(make_pair(i+1, idx+1), k+1);
                        }
                        
                        if (count[i] == total / r) break;
                    }
                }
            }
            
            cout << ans.size() << endl;
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i].F.F << ' ' << ans[i].F.S << ' ' << ans[i].S << endl;
            }
        }
    }
}