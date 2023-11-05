#include <bits/stdc++.h> 
using namespace std; 
 
#define ll long long int
#define mod  1000000007 
 
int main()
{
        ll n,i,j,k,j1;
        cin>>n;
        ll a[n-2][3];
        vector<ll>v[n+1];
        for(i=0;i<n-2;i++)
        {
        	cin>>a[i][0]>>a[i][1]>>a[i][2];
        	v[a[i][0]].push_back(i);
        	v[a[i][1]].push_back(i);
        	v[a[i][2]].push_back(i);
        }
 
        vector<ll>ans;
 
        ll p=-1,a1,a2,a0;
        for(i=1;i<=n && p==-1;i++)
        {
        	if(v[i].size()==1)
        	{
        		ans.push_back(i);p=v[i][0];
        	}
        }
 
        // cout<<p<<" "<<ans[0]<<endl;
 
        if(v[a[p][0]].size()==2)
        	ans.push_back(a[p][0]);
        else if(v[a[p][0]].size()==3)
        	a1=a[p][0];
        if(v[a[p][1]].size()==2)
        	ans.push_back(a[p][1]);
        else if(v[a[p][1]].size()==3)
        	a1=a[p][1];
        if(v[a[p][2]].size()==2)
        	ans.push_back(a[p][2]);
        else if(v[a[p][2]].size()==3)
        	a1=a[p][2];
        ans.push_back(a1);
 
        // cout<<ans[0]<<" "<<ans[1]<<" "<<ans[2]<<endl;
        ll c=10;
        while(ans.size()!=n)
        {
        	a1=ans[ans.size()-1];
        	a2=ans[ans.size()-2];
        	a0=ans[ans.size()-3];
        	p=-1;
        	for(i=0;i<v[a1].size() && p==-1;i++)
        	{
        		for(j=0;j<v[a2].size() && p==-1;j++)
        		{
        			if(v[a1][i]==v[a2][j])
        			{
        				p=v[a1][i];
        				for(j1=0;j1<v[a0].size();j1++)
        					if(v[a0][j1]==v[a1][i])
        						p=-1;
        			}
        		}
        	}
        	// cout<<p<<endl;
        	if(p!=-1)
        	{
        		if(a[p][0]!=a1 && a[p][0]!=a2)
        			ans.push_back(a[p][0]);
        		if(a[p][1]!=a1 && a[p][1]!=a2)
        			ans.push_back(a[p][1]);
        		if(a[p][2]!=a1 && a[p][2]!=a2)
        			ans.push_back(a[p][2]);
        	}
 
        } 
        for(i=0;i<n;i++)
        	cout<<ans[i]<<" ";
        cout<<endl;   
    return 0;
}