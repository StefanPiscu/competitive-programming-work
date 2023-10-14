#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353
#define int long long

void solve(){
  int n;
  cin>>n;
  vector<int> v(n+1);
  int sol=0;
  for(int i=1;i<=n;++i) cin>>v[i];
  vector<unordered_map<int, int>> dp(2);
  v[0]=1;
  for(int i=n;i;--i){
    int l=i%2;
    int lp=!l;
    dp[l][v[i]]=1;
    for(auto it:dp[lp]){
      int x=it.first, val=it.second;
      int nrsplits=(v[i]+x-1)/x;
      dp[l][v[i]/nrsplits]+=val;
      sol+=((nrsplits-1)*val%MOD)*i%MOD;
      sol%=MOD;
    }
    dp[lp].clear();
  }
  dp[0].clear();
  dp[1].clear();
  cout<<sol<<"\n";
}

int32_t main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}