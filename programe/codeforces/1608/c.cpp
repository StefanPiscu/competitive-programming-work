#include <bits/stdc++.h>
using namespace std;

void solve(){
  int n;
  cin>>n;
  vector<pair<int, int>> va(n+1), vb(n+1);
  vector<int> a(n+1), b(n+1);
  for(int i=1;i<=n;++i){
    cin>>va[i].first;
    va[i].second=i;
  }
  sort(va.begin()+1, va.end(), greater<pair<int, int>>());
  for(int i=1;i<=n;++i){
    a[va[i].second]=i;
  }
  for(int i=1;i<=n;++i){
    cin>>vb[i].first;
    vb[i].second=i;
  }
  sort(vb.begin()+1, vb.end(), greater<pair<int, int>>());
  for(int i=1;i<=n;++i){
    b[vb[i].second]=i;
  }
  int poza=1, pozb=1;
  int i=1, j=1;
  vector<int> sol(n+1);
  while(i<=poza||j<=pozb){
    if(i<=poza){
      sol[va[i].second]=1;
      pozb=max(pozb, b[va[i].second]);  
      i++;
    }
    else if(j<=pozb){
      sol[vb[j].second]=1;
      poza=max(poza, a[vb[j].second]);
      j++;
    }
  }
  for(int i=1;i<=n;++i) cout<<sol[i];
  cout<<"\n";
}

int main(){
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}