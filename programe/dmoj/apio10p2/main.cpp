#include <bits/stdc++.h>
using namespace std;

int n, k;

struct nod{
  int dp[5]={0, 0, 0, 0, 0};
  vector<int> out;

};


vector<nod> g;

void dfs(int x, int fat){
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfs(it, x);
    for(int i=4;i>=0;--i){
      if(i<3) g[x].dp[i+2]=max(g[x].dp[i+2], g[it].dp[2]+g[x].dp[i]);
      if(i<4) g[x].dp[i+1]=max(g[x].dp[i+1], g[it].dp[1]+g[x].dp[i]+1);
    }
  }
}

void topdown(int x, int fat, int dp1, int dp2){
  for(int i=4;i>=0;--i){
    if(i<3) g[x].dp[i+2]=max(g[x].dp[i+2], dp2+g[x].dp[i]);
    if(i<4&&fat) g[x].dp[i+1]=max(g[x].dp[i+1], dp1+g[x].dp[i]);
  }
  vector<int> maxi1(g[x].out.size(), dp1), maxi2(g[x].out.size(), dp2);
  int crmax1=dp1, crmax2=dp2;
  for(int i=0;i<g[x].out.size();++i){
    if(g[x].out[i]==fat) continue;

    maxi1[i]=max(maxi1[i], crmax1);
    maxi2[i]=max(maxi2[i], crmax2);
    crmax1=max(crmax1, g[g[x].out[i]].dp[1]+1);
    crmax2=max(crmax1, g[g[x].out[i]].dp[2]);
  }
  crmax1=dp1, crmax2=dp2;
  for(int i=g[x].out.size()-1;i>=0;--i){
    if(g[x].out[i]==fat) continue;
    maxi1[i]=max(maxi1[i], crmax1);
    maxi2[i]=max(maxi2[i], crmax2);
    crmax1=max(crmax1, g[g[x].out[i]].dp[1]+1);
    crmax2=max(crmax1, g[g[x].out[i]].dp[2]);
  }
  for(int i=0;i<g[x].out.size();++i){
    auto it=g[x].out[i];
    if(it==fat) continue;
    topdown(it, x, maxi1[i]+1, maxi2[i]);
  }
}

int main(){
  cin>>n>>k;
  g.resize(n+1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    g[a].out.push_back(b);
    g[b].out.push_back(a);
  }
  dfs(1, 0);
  topdown(1, 0, 0, 0);
  int ans=0;
  for(int i=1;i<=n;++i){
    if(k==1) ans=max({ans, g[i].dp[1], g[i].dp[2]});
    else ans=max({ans, g[i].dp[1], g[i].dp[2], g[i].dp[3], g[i].dp[4]});
  }
  cout<<2*(n-1)+k-ans<<"\n";
  return 0;
}