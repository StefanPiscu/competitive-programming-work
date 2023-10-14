#include <bits/stdc++.h>
using namespace std;


int main(){
  int t;
  cin>>t;
  while(t--){
    int x, y;
    cin>>x>>y;
    if(x>y) cout<<(x+y)<<"\n";
    else if(x==y) cout<<x<<"\n";
    else{
      cout<<y-(y%x)/2<<"\n";
    }
  }
}