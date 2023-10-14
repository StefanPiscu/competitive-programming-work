#include <bits/stdc++.h>
using namespace std;

string s;
int nra, nrb, nrc;
int nrab, nrac, nrbc;

int main(){
  int n=0;
  cin>>n;
  cin>>s;
  n=s.size();
  s='$'+s;
  for(int i=1;i<=n;++i){
    if(s[i]=='A') nra++;
    if(s[i]=='B') nrb++;
    if(s[i]=='C') nrc++;
  }
  // nra=nrab+nrac
  // nrb=nrab+nrbc
  // nrc=nrac+nrbc
  // nrab=nra+nrb-nrc/2;
  nrab=(nra+nrb-nrc)/2;
  nrac=(nra+nrc-nrb)/2;
  nrbc=(nrb+nrc-nra)/2;
  int bal=0, auxab=nrab, auxac=nrac, auxbc=nrbc;
  queue<int> open;
  vector<pair<int, int>> sol;
  for(int i=n;i&&nrab;--i){
    if(s[i]=='B'&&auxab) auxab--, open.push(i), s[i]='*';
    if(s[i]=='A'&&!open.empty()){
      nrab--, s[i]='*';
      int x=open.front();
      open.pop();
      sol.push_back({i, x});
    }
  }
  if(nrab!=0){
    cout<<"NO\n";
    return 0;
  }
  assert(open.empty());
  for(int i=1;i<=n&&nrbc;++i){
    if(s[i]=='B'&&auxbc) auxbc--, open.push(i), s[i]='*';
    if(s[i]=='C'&&!open.empty()){
      nrbc--, s[i]='*';
      int x=open.front();
      open.pop();
      sol.push_back({x, i});
    }
  }
  if(nrbc!=0){
    cout<<"NO\n";
    return 0;
  }
  assert(open.empty());
  for(int i=1;i<=n&&nrac;++i){
    if(s[i]=='A'&&auxac) auxac--, open.push(i), s[i]='*';
    if(s[i]=='C'&&!open.empty()){
      nrac--, s[i]='*';
      int x=open.front();
      open.pop();
      sol.push_back({x, i});
    }
  }
  if(nrac!=0){
    cout<<"NO\n";
    return 0;
  }
  cout<<"YES\n";
  for(auto it:sol){
    cout<<it.first<<" "<<it.second<<"\n";
  }
  return 0;
}