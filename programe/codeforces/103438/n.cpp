#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
  int n;
  cin>>n;
  n++;
  vector<int> a(n+1), b(n+1);
  for(int i=1;i<=n;++i) cin>>a[i];
  for(int i=1;i<=n;++i) cin>>b[i];
  int sol=0;
  for(int i=n;i;--i){
    if(b[i]<a[i]) continue;
    else{
      int dif=b[i]-a[i];
      int cnt=(dif+1)/2;
      a[i-1]-=cnt;
      sol+=cnt;
    }
  }
  if(a[0]==0) cout<<sol<<"\n";
  else cout<<"-1\n";
}