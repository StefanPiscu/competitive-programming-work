#include <bits/stdc++.h>
using namespace std;

#define MOD 998244352
#define int long long

int n, k;

struct nod{
  int deg;
  int sz;
  vector<vector<int>> dp;
  vector<int> findp; // dp[i][1]*2+dp[i][2]*3...dp[i][x]*(x+1)
  vector<int> dpsum;
  vector<int> out;
};
vector<nod> g;

void preproc(int x, int fat){
  g[x].sz=1;
  for(auto it:g[x].out){
    if(it==fat) continue;
    g[x].deg++;
    preproc(it, x);
    g[x].sz+=g[it].sz;
  }
  g[x].dp.resize(k+2, vector<int>(g[x].deg+1));
  g[x].findp.resize(k+2);
  g[x].dpsum.resize(k+2);
  g[x].dp[0][0]=1;
}



void dfs(int x, int fat){
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfs(it, x);
  }
  for(auto it:g[x].out){
    if(it==fat) continue;
    int bndk=min(k, g[x].sz-1);
    for(int i=bndk;i>=0;--i){
      for(int i2=0;i2<=min(i, g[it].sz-1);++i2){
        int bnd=min(g[x].deg, i-i2+1);
        for(int j=0;j<=bnd;++j){
          if(i2) g[x].dp[i][j]+=g[x].dp[i-i2][j]*g[it].dpsum[i2];
          g[x].dp[i][j]%=MOD;
          if(j) g[x].dp[i+1][j]+=(g[x].dp[i-i2][j-1]*g[it].findp[i2])%MOD*j;
          g[x].dp[i+1][j]%=MOD;
        }
      }
    }
  }
  for(int i=0;i<=k;++i){
    for(int j=0;j<=min(g[x].deg, i);++j){
      g[x].findp[i]+=g[x].dp[i][j]*(j+1);
      g[x].dpsum[i]+=g[x].dp[i][j];
      g[x].findp[i]%=MOD;
      g[x].dpsum[i]%=MOD;
    }
  }
}

int32_t main(){
  cin>>n>>k;
  g.resize(n+1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    g[a].out.push_back(b);
    g[b].out.push_back(a);
  }
  preproc(1, 0);
  dfs(1, 0);
  int sol=0;
  for(int j=0;j<=g[1].deg;++j) sol+=g[1].dp[k][j], sol%=MOD;
  cout<<sol<<"\n";
}