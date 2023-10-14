#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
  int n;
  cin>>n;
  vector<int> v(n+1);
  for(int i=1;i<=n;++i) cin>>v[i];
  vector<int> sp1(n+2), sp2(n+2);
  for(int i=1;i<=n;++i){
    sp1[i]=sp1[i-1]+v[i]*v[i];
  }
  for(int i=n;i;--i) sp2[i]=sp2[i+1]+v[i];
  int val=0;
  for(int i=1;i<n;++i){
    val=max(val, sp1[i]*sp2[i+1]);
  }
  cout<<val<<"\n";
}