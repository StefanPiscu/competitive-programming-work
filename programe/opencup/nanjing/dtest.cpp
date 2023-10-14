#include <bits/stdc++.h>
using namespace std;

int main(){
  int t;
  cin>>t;
  int n;
  cin>>n;
  vector<int> w(n+1);
  for(int i=1;i<=n;++i) cin>>w[i];
  for(int k=1;k<=n;++k){ 
    int nr=0;
    vector<int> v(n+1);
    for(int i=1;i<=n;++i) v[i]=w[i];
    for(int i=1;i<=k;++i){
      for(int j=1;j<=k;++j){
        if(v[i]<v[j]) swap(v[i], v[j]), nr++;
        /*
        for(int i=1;i<=n;++i){
          cout<<v[i]<<" ";
        }
        cout<<"\n";
        */
      }
      /*
      cout<<nr<<"\n";
      for(int i=1;i<=n;++i){
        cout<<v[i]<<" ";
      }
      cout<<"\n";
      */
    }
    cout<<nr<<" "; 
  }
  cout<<"\n";
  return 0;
}