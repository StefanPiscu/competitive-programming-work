#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, k;
vector<int> v;

bool checkmin(int x){
  int nrop=k;
  for(int i=1;i<=n;++i){
    if(v[i]<x) nrop-=(x-v[i]);
  }
  if(nrop<0) return 0;
  return 1;
}

bool checkmax(int x){
  int nrop=k;
  for(int i=1;i<=n;++i){
    if(v[i]>x) nrop-=(v[i]-x);
  }
  if(nrop<0) return 0;
  return 1;
}

int32_t main(){
  cin>>n>>k;
  v.resize(n+1);
  for(int i=1;i<=n;++i){
    cin>>v[i];
  }
  int mini=v[1], maxi=v[1];
  for(int i=2;i<=n;++i){
    mini=min(mini, v[i]);
    maxi=max(maxi, v[i]);
  }
  #define mid ((st+dr)/2)
  int st=0, dr=2e9, solmin=maxi;
  while(st<=dr){
    if(checkmin(mid)){
      solmin=mid;
      st=mid+1;
    }
    else{
      dr=mid-1;
    }
  }
  int nrop=k;
  for(int i=1;i<=n;++i){
    if(solmin>v[i]){
      nrop-=(solmin-v[i]);
      v[i]=solmin;
    } 
  }
  for(int i=1;i<=n&&nrop;++i){
    if(v[i]==solmin) v[i]++, nrop--;
  }
  mini=v[1], maxi=v[1];
  for(int i=2;i<=n;++i){
    mini=min(mini, v[i]);
    maxi=max(maxi, v[i]);
  }
  st=0, dr=2e9;
  int solmax=0;
  while(st<=dr){
    if(checkmax(mid)){
      solmax=mid;
      dr=mid-1;
    }
    else{
      st=mid+1;
    }
  }
  nrop=k;
  for(int i=1;i<=n;++i){
    if(solmax<v[i]){
      nrop-=(v[i]-solmax);
      v[i]=solmax;
    } 
  }
  for(int i=1;i<=n&&nrop;++i){
    if(v[i]==solmax) v[i]--, nrop--;
  }
  mini=v[1], maxi=v[1];
  for(int i=2;i<=n;++i){
    mini=min(mini, v[i]);
    maxi=max(maxi, v[i]);
  }
  cout<<maxi-mini<<"\n";
}