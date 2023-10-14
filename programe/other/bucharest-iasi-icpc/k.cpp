#include <bits/stdc++.h>
using namespace std;

void solve(){
  int n;
  cin>>n;
  vector<int> sum(n+1);
  for(int i=1;i<=n;++i){
    int k;
    cin>>k;
    while(k--){
      int x;
      cin>>x;
      sum[i]+=x;
    }
  }
  sort(sum.begin()+1, sum.end());
  long long sol=0;
  for(int i=1;i<=n;++i){
    sol+=1LL*(n-i+1)*sum[i];
  }
  cout<<setprecision(10)<<fixed<<double(sol)/double(n)<<"\n";
}

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}