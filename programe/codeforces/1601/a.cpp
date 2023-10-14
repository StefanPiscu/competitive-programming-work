#include <bits/stdc++.h>
using namespace std;

int fr[31];

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    for(int i=0;i<=30;++i) fr[i]=0;
    int n;
    cin>>n;
    for(int i=1;i<=n;++i){
      int x;
      cin>>x;
      for(int j=0;(1<<j)<=x;j++){
        if(x&(1<<j)) fr[j]++;
      }
    }
    int x=0;
    for(int i=0;i<=30;++i){
      if(fr[i]) x=__gcd(fr[i], x);
    }
    for(int i=1;i<=n;++i) if(x%i==0) cout<<i<<" ";
    cout<<"\n";
  }
  return 0;
}
