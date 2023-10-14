#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> poz, per;

vector<int> getper(){
  vector<int> key(n+1);
  for(int i=1;i<=n;++i){
    key[poz[i]]=i;
  }
  vector<int> sol(n+1);
  for(int i=1;i<=n;++i)sol[i]=key[per[i]];
  return sol;
}

int main(){
  cin.tie(0);
  cin>>n>>m;
  poz.resize(n+1);
  per.resize(n+1);
  for(int i=1;i<=n;++i) per[i]=poz[i]=i;
  while(m--){
    char t;
    cin>>t;
    if(t=='B'){
      int a, b;
      cin>>a>>b;
      swap(poz[a], poz[b]);
    }
    else if(t=='E'){
      int a, b;
      cin>>a>>b;
      swap(per[a], per[b]);
    }
    else{
      vector<int> fperm=getper();
      vector<int> key(n+1);
      for(int i=1;i<=n;++i) cin>>key[i];
      vector<int> sol(n+1);
      for(int i=1;i<=n;++i) sol[fperm[i]]=key[i];
      for(int i=1;i<=n;++i){
        cout<<sol[i];
        if(i!=n) cout<<" ";
      }
      cout<<"\n";
    }
  }
  return 0;
}