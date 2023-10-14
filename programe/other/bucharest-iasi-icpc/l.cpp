#include <bits/stdc++.h>
using namespace std;

int deg[5];
int main(){
  for(int i=1;i<=3;++i){
    int a, b;
    cin>>a>>b;
    deg[a]++;
    deg[b]++;
    if(deg[a]>2){
      cout<<"NO\n";
      return 0;
    }
    if(deg[b]>2){
      cout<<"NO\n";
      return 0;
    }
  }
  cout<<"YES\n";
  return 0;
}