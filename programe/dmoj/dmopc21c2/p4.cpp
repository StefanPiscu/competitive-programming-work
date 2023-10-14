#include <bits/stdc++.h>
using namespace std;

int n, k;
// dp [elem], int coming from left, coming from right
vector<int> a;
vector<pair<int, int>> vals;
int dp[1000003][2][2];

int main(){
  cin>>n>>k;
  a.resize(n+1);
  vals.push_back({0, 0});
  for(int i=1;i<=n;++i){
    cin>>a[i];
    if(a[i]!=vals.back().first) vals.push_back({a[i], 1});
    else vals.back().second++;
  }
  //for(auto it:vals) cout<<it.first<<" "<<it.second<<"\n";
  //cout.flush();

  for(int i=1;i<vals.size();++i){
    for(int pre=0;pre<2;++pre){
      for(int nex=0;nex<2;++nex){
        int val=vals[i].second;
        if(i!=1&&pre){
          if(vals[i-1].first<vals[i].first) val++;
          else val-=(k+1);
        }
        if((i+1)!=vals.size()&&nex){
          if(vals[i+1].first<vals[i].first) val++;
          else val-=(k+1);
        }
        if(val<=0) dp[i][pre][nex]=min(dp[i-1][0][pre], dp[i-1][1][pre]);
        else dp[i][pre][nex]=min(dp[i-1][0][pre], dp[i-1][1][pre])+(val-1)/(2*k+1)+1;
        //cout<<i<<" "<<pre<<" "<<nex<<" "<<dp[i][pre][nex]<<"\n";
      }
    }
  }
  cout<<min(dp[vals.size()-1][0][0], dp[vals.size()-1][1][0])<<"\n";
  return 0;
}