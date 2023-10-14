#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MOD 1000000007

vector<int> bases;
vector<vector<int>> vals;
vector<vector<int>> pows;

void calchash(string s){
  bases.clear();
  vals.clear();
  pows.clear();
  bases.resize(2+1);
  for(int i=1;i<bases.size();++i) bases[i]=rand()+30;
  vals.resize(2+1, vector<int>(s.size(), 0));
  pows.resize(2+1, vector<int>(s.size()+1, 1));
  for(int i=1;i<s.size();++i){
    int val=s[i]-'a';
    for(int j=1;j<bases.size();++j){
      vals[j][i]=(1LL*vals[j][i-1]*bases[j]%MOD+val)%MOD;
      pows[j][i]=pows[j][i-1]*bases[j]%MOD;
    }
  }  
}

int gethash(int l, int r, int b){
  return (vals[b][r]-vals[b][l-1]*pows[b][r-l+1]%MOD+MOD)%MOD;
}


bool areeq(int l1, int r1, int l2, int r2){
  for(int i=0;i<bases.size();++i){
    if(gethash(l1, r1, i)!=gethash(l2, r2, i)) return 0;
  }
  return 1;
}

void solve(){
  string s;
  cin>>s;
  s='$'+s;
  calchash(s);
  int nr=0, p=1, q=1;
  bool ok=(s.size()-1)%2;
  while(2*p<s.size()){
    if(2*q>=s.size()){
      nr++;
      ok=0;
      break;
    }
    if(areeq(p, q, s.size()-q, s.size()-p)) p=q+1, q=p, nr+=2;
    else q++;
  }
  cout<<nr+ok<<"\n";
}


int32_t main(){
  srand(time(0));
  int t;
  cin>>t;
  while(t--){
    solve();
  }
}