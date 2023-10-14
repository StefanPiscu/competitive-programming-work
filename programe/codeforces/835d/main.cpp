#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define int long long

string s;

vector<int> bases;
vector<vector<int>> vals, rvals, pows;

void calchash(string s){
  bases.resize(1+1);
  for(int i=1;i<bases.size();++i) bases[i]=rand()+30;
  bases[1]=27;
  vals.resize(1+1, vector<int>(s.size(), 0));
  rvals.resize(1+1, vector<int>(s.size()+1, 0));
  pows.resize(1+1, vector<int>(s.size(), 1));
  for(int i=1;i<s.size();++i){
    int val=s[i]-'a';
    for(int j=1;j<bases.size();++j){
      vals[j][i]=(1LL*vals[j][i-1]*bases[j]%MOD+val)%MOD;
      pows[j][i]=1LL*pows[j][i-1]*bases[j]%MOD;
    }
  }
  for(int i=s.size()-1;i;--i){
    int val=s[i]-'a';
    for(int j=1;j<bases.size();++j){
      rvals[j][i]=(1LL*rvals[j][i+1]*bases[j]%MOD+val)%MOD;
    }
  }
}

int gethash(int l, int r, int b){
  //cout<<l<<" "<<r<<" "<<(vals[b][r]-1LL*vals[b][l-1]*pows[b][(r-l+1)]%MOD)%MOD<<"*********"<<endl;
  return (vals[b][r]-1LL*vals[b][l-1]*pows[b][(r-l+1)]%MOD+MOD)%MOD;
}

int getrhash(int l, int r, int b){
  //cout<<l<<" "<<r<<" "<<(rvals[b][l]-1LL*rvals[b][r+1]*pows[b][(r-l+1)]%MOD)%MOD<<"|||||||||||"<<endl;
  return (rvals[b][l]-1LL*rvals[b][r+1]*pows[b][(r-l+1)]%MOD+MOD)%MOD;
}

bool iseq(int l1, int r1, int l2, int r2){
  for(int i=1;i<bases.size();++i){
    if(gethash(l1, r1, i)!=getrhash(l2, r2, i)) return 0;
  } 
  return 1;
}

int32_t main(){
  srand(time(0));
  cin>>s;
  s='$'+s;
  calchash(s);
  vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
  vector<int> sol(s.size());
  for(int i=1;i<s.size();++i) dp[i][i]=1;
  sol[1]+=s.size()-1;
  for(int l=2;l<s.size();++l){
    for(int i=1;i+l-1<s.size();++i){
      int j=i+l-1;
      if(iseq(i, i+l/2-1, j-l/2+1, j)) dp[i][j]=dp[i][i+l/2-1]+1;
      sol[dp[i][j]]++;
      //cout<<i<<" "<<j<<" "<<dp[i][j]<<endl;
    }
  }
  for(int i=s.size()-1;i;--i) sol[i-1]+=sol[i];
  for(int i=1;i<s.size();++i) cout<<sol[i]<<" ";
  cout<<"\n";
  return 0;
}