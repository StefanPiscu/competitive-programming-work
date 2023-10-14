#include <bits/stdc++.h>

using namespace std;

void solve(int n){
  for(int i=2;i*(i+1)/2<=n;++i){
    int rest=n-i*(i+1)/2;
    if(rest%i==0){
      int base=rest/i;
      cout<<n<<" = ";
      for(int j=1;j<=i;++j){
        cout<<base+j<<" ";
        if(j!=i) cout<<"+ ";
      }
      cout<<"\n";
      return;
    }
  }
  cout<<"IMPOSSIBLE\n";
}

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    int x;
    cin>>x;
    solve(x);
  }
}