#include <bits/stdc++.h>
using namespace std;
int cnt[1000005], arr[300005];
bool mul(int id){
    for(int i=2; i*id<=1000000; ++i){
        if(cnt[i*id]>0){
            return true;
        }
    }
    return false;
}
void solve(){
    int n;
    set<pair<int, int>> s;
    cin >> n;
    for(int i=0; i<n; ++i){
        int tmp;
        cin >> tmp;
        cnt[tmp]++;
    }
    for(int i=1; i<=1000000; ++i){
        if(cnt[i]>0){
            s.insert(make_pair(cnt[i], i));
        }
    }
    multiset<int> msp;
    arr[0] = s.size();
    int cod = 1, pro = 1;
    while(!s.empty() && arr[pro-1]>1){
        auto it = s.begin();
        int amp = (*it).first, id = (*it).second;
        if(amp<=cod){
            if(mul(id)){
                arr[pro] = arr[pro-1]-1;
                s.erase(it);
                cod-=amp;
            }
            else{
                //arr[pro] = arr[pro-1];
                s.erase(it);
                msp.insert(amp);
                pro--;
                cod--;
            }
        }
        else{
            arr[pro] = arr[pro-1];
        }
        pro++;
        cod++;
    }
    //cout << pro << '\n';
    bool flag = 0;
    while(!msp.empty() && arr[pro-1]>1){
        auto it = msp.begin();
        int amp = (*it);
        if(amp<=cod){
            arr[pro] = arr[pro-1]-1;
            msp.erase(it);
            cod-=amp;
            if(!flag){
                arr[pro]++;
                flag = 1;
            }
        }
        else{
            arr[pro] = arr[pro-1];
        }
        pro++;
        cod++;
    }
    for(int i=pro; i<=n; ++i){
        arr[i] = 1;
    }
    for(int i=0; i<=n; ++i){
        cout << arr[i] << " \n"[i==n];
    }
}
int main(){
    # define infile "equal.in"
    # define outfile "equal.out"
 
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    int t = 1;
    //cin >> t;
    while(t--){
        solve();
    }
    return 0;
}