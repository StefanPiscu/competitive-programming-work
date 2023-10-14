#include <bits/stdc++.h>
using namespace std;

int t;

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);

  cin>>t;
  while(t--){
    int n;
    cin>>n;
    if(n==1){
      int x;
      cin>>x;
      cout<<x<<"\n";
    }
    else{
      bool hasn=0, hasp=0;
      int mini=1e9+5, maxi=-1e9-5;
      long long sol=0;
      for(int i=1;i<=n;++i){
        int x;
        cin>>x;
        sol+=abs(x);
        if(x>0) hasp=1;
        if(x<0) hasn=1;
        mini=min(mini, x);
        maxi=max(maxi, x);
      }
      if(!hasn) sol-=2LL*mini;
      if(!hasp) sol+=2LL*maxi;
      cout<<sol<<"\n";

    }
  }

}
