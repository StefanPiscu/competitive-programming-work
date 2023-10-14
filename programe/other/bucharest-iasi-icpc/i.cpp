#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 998244353

int n, sum;
vector<int> a;
vector<vector<int>> dp, dp2;

int binpow(int b, int e){
  int sol=1;
  while(e){
    if(e&1) sol=sol*b%MOD;
    b=b*b%MOD;
    e>>=1;
  }
  return sol;
}

int32_t main(){
  cin>>n;
  a.resize(n+1);
  for(int i=1;i<=n;++i) cin>>a[i], sum+=a[i];
  dp.resize(n+1, vector<int>(sum+1, 0));
  dp2.resize(n+1, vector<int>(sum+1, 0));
  dp[0][0]=dp2[0][0]=1;
  int crs=0;
  for(int i=1;i<=n;++i){
    crs+=a[i];
    for(int j=0;j<=crs;++j){
      dp[i][j]+=dp[i-1][j]*2;
      dp2[i][j]+=dp2[i-1][j];
      if(j>=a[i]) dp[i][j]+=dp[i-1][j-a[i]];
      if(j>=a[i]) dp2[i][j]+=dp2[i-1][j-a[i]];
      dp[i][j]%=MOD;
      dp2[i][j]%=MOD;
    }
  }
  //for(int i=0;i<=sum;++i) cout<<dp[n][i]<<" ";
  //cout<<"\n";
  int sol=0;
  for(int j=(sum+1)/2;j<=sum;++j) sol+=dp[n][j], sol%=MOD;
  //cout<<sol<<"*****\n";
  //cout<<dp2[n][sum/2]<<"\n";
  if(sum%2==0) sol=(sol+MOD-dp2[n][sum/2])%MOD;
  cout<<(binpow(3, n)-3*sol%MOD+3LL*MOD)%MOD<<"\n";
  return 0;
}