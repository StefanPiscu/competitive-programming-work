#include <bits/stdc++.h>
using namespace std;

struct nod{
  pair<int, int> dp[4];
  vector<int> out;
};

int n;
vector<nod> g;

void dfs(int x, int fat){
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfs(it, x);
    int val=g[it].dp[1].first+1;
    for(int i=3;i>=0;--i){
      if(g[x].dp[i].first==val) g[x].dp[i].second+=g[it].dp[1].second;
      else if(g[x].dp[i].first<val) g[x].dp[i].first=val;
    }
  }
}

void topdown(int x, int fat, pair<int, int> dp){
  int val=dp.first;
  for(int i=3;i>=0;--i){
    if(g[x].dp[i].first==val) g[x].dp[i].second+=dp.second;
    else if(g[x].dp[i].first<val) g[x].dp[i].first=val;
  }
  vector<pair<int, int>> maxdp(g[x].out.size());
  pair<int, int> crmax=dp;
  for(int i=0;i<maxdp.size();++i){
    auto it=g[x].out[i];
    if(it==fat) continue;
    maxdp[i]=crmax;
    crmax=max(crmax, g[it].dp1);
  }
  crmax=dp;
  for(int i=maxdp.size()-1;i>=0;--i){
    auto it=g[x].out[i];
    if(it==fat) continue;
    maxdp[i]=crmax;
    crmax=max(crmax, g[it].dp1);
  }
  for(int i=0;i<g[x].out.size();++i){
    auto it=g[x].out[i];
    if(it==fat) continue;
    topdown(it, x, {maxdp[i].first+1, maxdp[i].second});
  }
}

int main(){
  cin>>n;
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    g[a].out.push_back(b);
    g[b].out.push_back(a);
  }
  dfs(1, 0);
  topdown(1, 0, {0, 0});
  int sol=0, solval=0;
  for(int i=1;i<=n;++i){
    int val=g[i].dp1.first*(g[i].dp2.first+g[i].dp3.first);
    if(val>solval) solval=val, sol=i;
    else if(val==solval);
  }
  cout<<sol<<"\n";
}