#include <bits/stdc++.h>
using namespace std;

int t;

vector<int> sol;

void solve(int l, int r){
  for(int i=l;i<=r-2;i+=2){
    sol.push_back(i);
  }
  for(int i=r-4;i>=l;i-=2){
    sol.push_back(i);
  }
}

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    vector<int> a(n+1);
    int xorsum=0;
    for(int i=1;i<=n;++i){
      cin>>a[i];
      xorsum^=a[i];
    }
    if(xorsum==1){
      cout<<"NO\n";
      continue;
    }
    sol.clear();
    if(n&1) solve(1, n);
    else{
      xorsum=0;
      int ok=1;
      for(int i=1;i<=n;++i){
        xorsum^=a[i];
        if((xorsum==0)&&(i&1)){
          solve(1, i), solve(i+1, n);
          ok=0;
          break;
        }
      }
      if(ok){
        cout<<"NO\n";
        continue;
      }
    }
    cout<<"YES\n";
    cout<<sol.size()<<"\n";
    for(auto it:sol) cout<<it<<" ";
    cout<<"\n";
  }
}