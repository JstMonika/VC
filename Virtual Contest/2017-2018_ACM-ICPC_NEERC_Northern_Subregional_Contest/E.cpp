#include <bits/stdc++.h>
using namespace std;

const int mxn = 1e6 + 5;
int ans[300005];
vector<int> v[2];
map<int, int> mp;

bool solve(){
    mp.clear();
    v[0].clear();
    v[1].clear();
    
    memset(ans, 0x3f, sizeof(ans));

    int n; cin >> n;
    if (!n) return false;
    for (int i = 0, x; i < n; i++) {
        cin >> x;
        mp[x]++;
    }

    for (auto it = mp.begin(); it != mp.end(); it++)
    {
        v[0].emplace_back(it->second);
        int x = it->first;
        for (int i = 2 * x; i < mxn; i += x)
        {
            if (mp.count(i)) {
                v[1].emplace_back(it->second);
                break;
            }
        }
    }
    
    sort(v[0].begin(), v[0].end());
    sort(v[1].begin(), v[1].end());
    for (int i = 0; i < 2; i++) {
        for (auto k : v[i])
        cout << k << ' ';
        cout << endl;
    }
    int num = mp.size();
    ans[0] = num;

    int sum = 0;
    for (int i = 0; i < v[0].size(); i++)
    {
        sum += v[0][i];
        if (sum == 7) cout << ans[sum] << ' ' << num-i << endl;
        ans[sum] = min(ans[sum], num - i);
    }
    
    sum = 0;
    for (int i = 0; i < v[1].size(); i++)
    {
        sum += v[1][i];
        if (sum == 7) cout << ans[sum] << ' ' << num-i-1 << endl;
        ans[sum] = min(ans[sum], num - i - 1);
    }
    
    cout << ans[0] << " ";
    for (int i = 1; i <= n; i++)
    {
        cout << (ans[i] = min(ans[i], ans[i - 1])) << " ";
    }
    
    cout << '\n';
    return true;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    # define infile "equal.in"
    # define outfile "equal.out"

    // freopen(infile, "r", stdin);
    // freopen(outfile, "w", stdout);
solve();
    return 0;
}