#include <bits/stdc++.h>
using namespace std;

#define int long long
#define bulan 1000ll

void solve(){
  int n;
  cin>>n;
  vector<int> a(n+1);
  for(int i=1;i<=n;++i){
    cin>>a[i];
  }
  int cnt=1;
  for(int i=1;i<=min(n, bulan);++i){
    int ok=0;
    for(int j=0;j<i;++j){
      if(a[i]%(i-j+1)!=0){
        ok=1;
        break;
      }
    }
    if(!ok){
      cout<<"NO\n";
      return;
    }
  }
  cout<<"YES\n";
  return;
}

int32_t main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}