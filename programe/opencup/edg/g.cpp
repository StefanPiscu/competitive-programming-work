#include <bits/stdc++.h>
using namespace std;

int n;
string s;

bool check(int x){
  int fuel=0;
  for(int i=1;i<=n;++i){
    if(s[i]=='0'){
      fuel--;
    }
    else{
      if(fuel<0){
        if(x<-fuel) return 0;
        else if(x==-fuel) fuel=x-1;
        else fuel=x;
      }
      else fuel=x;
    }
  }
  return fuel>=0;
}

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    cin>>n>>s;
    s='$'+s;
    int st=0, dr=n, sol=n;
    while(st<=dr){
      int mid=(st+dr)/2;
      if(check(mid)) sol=mid, dr=mid-1;
      else st=mid+1;
    }
    cout<<sol<<"\n";
  }
}