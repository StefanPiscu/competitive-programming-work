#include <bits/stdc++.h>
using namespace std;

int n, t;
vector<int> ans;
vector<vector<int>> fr;

long long eval(int nrc){
  long long cost=0;
  int nr=n;
  ans.clear();
  ans.resize(nrc+2, 0);
  for(int i=0;i<=t+1;++i) fr[i].clear();
  for(int i=nrc;i;--i) fr[1].push_back(i);
  for(int i=1;i<=t&&nr;++i){
    while(!fr[i].empty()&&nr){
      int x=fr[i].back();
      fr[i].pop_back();
      if((i+x)<=t) fr[i+x].push_back(x);
      nr--;
      cost+=i;
      ans[x]++;
    }
  }
  if(nr) return 1e18;
  else return cost+1ll*(nrc-1)*t;
}

int32_t main(){
  cin>>n>>t;
  fr.resize(t+2);
  //int goodsol=1e18;
  //for(int i=1;i<=n;++i) goodsol=min(eval(i), goodsol);
  int st=1, dr=n, sol=0;
  while(st<=dr){
    int mid=(st+dr)/2;
    long long val1=eval(mid), val2=eval(mid+1);
    //cout<<st<<" "<<dr<<" "<<mid<<" "<<val1<<" "<<val2<<" "<<sol<<"\n";
    if(val1>=1e18) st=mid+1, sol=mid;
    else if(val1>=val2) st=mid+1, sol=mid;
    else dr=mid-1;
  }
  cout<<eval(sol+1)<<"\n";
  cout<<sol<<"\n";
  for(int i=1;i<=sol;++i){
    cout<<ans[i]<<"\n";
    ans[i+1]+=ans[i];
  }
}