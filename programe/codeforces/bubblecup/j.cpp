#include <bits/stdc++.h>
using namespace std;

int main(){
  int n;
  cin>>n;
  vector<int> v(n+1);
  for(int i=1;i<=n;++i) cin>>v[i];
  vector<int> par, imp;
  map<int, int> fr;
  for(int i=1;i<=n;++i){
    if(fr.count(v[i])){
      int p1=fr[v[i]], p2=i;
      cout<<"YES\n";
      cout<<0<<" "<<v[i]<<" ";
      for(int i=1;i<=n;++i){
        if(i==p1||i==p2) continue;
        cout<<v[i]<<" ";
      }
      cout<<"\n";
      return 0;
    }
    fr[v[i]]=i;
    if(v[i]%2){
      imp.push_back(i);
      if(imp.size()>=2&&par.size()>=1){
        cout<<"YES\n";
        int sum=(v[imp[0]]+v[imp[1]]+v[par[0]])/2;
        int a=sum-v[imp[0]], b=sum-v[imp[1]], c=sum-v[par[0]];
        cout<<a<<" "<<b<<" "<<c<<" ";
        for(int i=1;i<=n;++i){
          if(i==imp[0]||i==imp[1]||i==par[0]) continue;
          cout<<v[i]-a<<" ";
        }
        cout<<"\n";
        return 0;
      }
    }
    else{
      par.push_back(i);
      if(par.size()>=3){
        cout<<"YES\n";
        int sum=(v[par[0]]+v[par[1]]+v[par[2]])/2;
        int a=sum-v[par[0]], b=sum-v[par[1]], c=sum-v[par[2]];
        cout<<a<<" "<<b<<" "<<c<<" ";
        cout.flush();
        for(int i=1;i<=n;++i){
          if(i==par[0]||i==par[1]||i==par[2]) continue;
          cout<<v[i]-a<<" ";
        }
        cout<<"\n";
        return 0;
      }
    }
  }
  map<int, pair<int, int>> difs;
  sort(v.begin()+1, v.end());
  for(int i=1;i<=n;++i){
    for(int j=i-1;j;--j){
      if(difs.count(v[i]-v[j])){
        int p1, p2;
        tie(p1, p2)=difs[v[i]-v[j]];
        if(p1==j){
          continue;
          cout<<"YES\n";
          cout<<v[p1]<<" "<<v[i]-v[p1]<<" "<<v[p2]-v[p1]<<" ";
          for(int k=1;k<=n;++k){
            if(k==p1||k==p2||k==i) continue;
            cout<<v[k]-v[p1]<<" ";
          }
          cout<<"\n";
          return 0;
        }
        cout<<"YES\n";
        cout<<0<<" "<<v[i]-v[j]<<" "<<v[j]<<" "<<v[p2]<<" ";
        for(int k=1;k<=n;++k){
          if(k==p1||k==p2||k==i||k==j) continue;
          cout<<v[k]<<" ";
        }
        cout<<"\n";
        return 0;
      }
      else difs[v[i]-v[j]]={i, j};
    }
  } 
  cout<<"NO\n";
  return 0;
}