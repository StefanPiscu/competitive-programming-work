#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, k;
vector<int> v;

bool check(int x){
  vector<int> dp(n+1, 1e9);
  int sol=1e9;
  for(int i=1;i<=n;++i){
    dp[i]=i-1;
    for(int j=i-1;j;--j){
      if(abs(v[j]-v[i])<=(x*(i-j))) dp[i]=min(dp[i], dp[j]+(i-j-1));
    }
    sol=min(sol, dp[i]+(n-i));
  }
  return sol<=k;
}


int32_t main(){
  cin>>n>>k;
  v.resize(n+1);
  int st=0, dr=0;
  for(int i=1;i<=n;++i) cin>>v[i], dr=max(dr, abs(v[i]));
  dr*=2;
  int sol=dr;
  while(st<=dr){
    int mid=(st+dr)/2;
    if(check(mid)) sol=mid, dr=mid-1;
    else st=mid+1;
  }
  cout<<sol<<"\n";
}