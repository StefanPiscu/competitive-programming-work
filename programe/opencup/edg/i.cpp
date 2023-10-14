#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    string s;
    cin>>s;
    s='$'+s;
    int sol=0, cnt=0;
    for(int i=n;i;--i){
      if(s[i]=='0') cnt++;
      else if(cnt) cnt--, sol+=i;
      else cnt++;
    }
    cout<<sol<<"\n";
  }
  return 0;
}