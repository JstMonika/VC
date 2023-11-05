#include<bits/stdc++.h>
using namespace std;
using pii = pair<int,int>;
int c2i(char c) {
	if(c>='A' && 'Z'>=c) {
		return c - 'A' + 26;
	} else {
		return c - 'a';
	}
}
vector<int> mp[60];
void init() {
	for(int i=0;i<60;i++)
		mp[i].clear();
}
priority_queue<pii> pq;
bool isv[60];
int mx[60];
int dij(int num, int s, int e) {
	while(!pq.empty()) pq.pop();
	for(int i=0;i<60;i++) {
		isv[i] = false;
		mx[i] = -1;
	}
	pq.emplace(make_pair(num,s));
	mx[s] = num;
	while(!pq.empty()) {
		pii now = pq.top();
		pq.pop();
		//printf("now.first = %d, now.second = %d\n",pq.top().first,pq.top().second);
		if(isv[now.second]) continue;
		if(now.second == e) return now.first;
		isv[now.second] = true;
		for(auto E:mp[now.second]) {
			int cost = now.first/20;
			if(now.first%20 != 0) cost++;
			if(E/26 == 0) cost = 1;
			if(now.first-cost < mx[E]) continue;
			mx[E] = now.first-cost;
			pq.emplace(make_pair(now.first-cost, E));
		}
	}
    
    return mx[e];
}

int lb(int goal, int S, int E) {
	int L = goal; int R = 1000000;
	int ans = R;
	while(L<R) {
		//printf("L = %d R = %d\n",L,R);
		int M = (L+R)/2;
		//printf("M = %d, dij = %d\n",M,dij(M,S,E));
		if(dij(M,S,E) >= goal) {
			ans = min(ans,R);
			R = M-1;
		}
		else L = M+1;
        
        memset(isv, 0, sizeof(isv));
        memset(mx, 0, sizeof(mx));
	} 
	//printf("R = %d\n",R);
	return ans;
} 
int main(){
	int n;
	int cnt = 1;
	while(1) {
		scanf("%d",&n);
		if(n == -1) break;
		init();
		char s,e;
		//printf("after init()\n");
		for(int i=0;i<n;i++) {
			scanf(" %c %c",&s,&e);
			mp[c2i(s)].emplace_back(c2i(e));
			mp[c2i(e)].emplace_back(c2i(s));
		}
		int goal,S,E;
		scanf("%d",&goal);
		scanf(" %c %c",&s,&e);
		S = c2i(s);
		E = c2i(e);
		//printf("go to LB\n");
		printf("Case %d: %d\n",cnt++,lb(goal,S,E));
	} 

}
