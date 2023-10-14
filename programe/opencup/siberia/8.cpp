#include <bits/stdc++.h>
using namespace std;

#define int long long

int t;

int32_t main(){
  cin>>t;
  while(t--){
    int a, b, r;
    cin>>a>>b>>r;
    int y=0;
    if(a<=r&&r<=b){
      cout<<r<<" "<<r+1<<"\n";
      continue;
    }
    if(r+1<=a-r) y=a-r;
    else if(r+1<=b-r) y=r+1;
    else{
      cout<<-1<<" "<<-1<<"\n";
      continue;
    }
    cout<<y+r<<" "<<y<<"\n";
  }
}