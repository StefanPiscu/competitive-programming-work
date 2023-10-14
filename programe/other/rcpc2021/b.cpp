#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin>>n;
  string s;
  cin>>s;
  s='$'+s;
  vector<int> dpA(n+1, 0);
  vector<int> dpB(n+1, 0);
  for(int i=1;i<=n;++i){
    //cout<<s[i]<<" ";
    if(s[i]=='A'){
      dpA[i]=min(dpA[i-1], dpB[i-1]+1);
      dpB[i]=min(dpB[i-1]+1, dpA[i-1]+1);
    }
    else{
      dpB[i]=min(dpB[i-1], dpA[i-1]+1);
      dpA[i]=min(dpA[i-1]+1, dpB[i-1]+1);
    }
    //cout<<i<<" "<<dpA[i]<<" "<<dpB[i]<<"\n";
  }
  cout<<dpA[n]<<"\n";
}