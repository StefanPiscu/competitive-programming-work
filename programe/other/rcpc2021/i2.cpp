#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int n;
string s;
int dp[204][204][204];
int lgput[30][204];

int binpow(int b, int e){
  if(lgput[b][e]) return lgput[b][e];
  int ob=b, oe=e;
  int sol=1;
  while(e){
    if(e&1) sol=sol*b%MOD;
    b=b*b%MOD;
    e>>=1;
  }
  return lgput[ob][oe]=sol;
}

int getsol(int sz, int l, int r){
  if(dp[sz][l][r]!=-1) return dp[sz][l][r];
  if(r==l) return dp[sz][l][r]=(binpow(26, sz)+MOD-binpow(25, sz))%MOD;
  if(r<l) return dp[sz][l][r]=(binpow(26, sz));
  if(sz==0) return dp[sz][l][r]=0;
  if(s[l]==s[r])  return dp[sz][l][r]=((0LL+getsol(sz-1, l+1, r-1)+1LL*getsol(sz-1, l, r)*25)%MOD);
  else return dp[sz][l][r]=((0LL+getsol(sz-1, l+1, r)+getsol(sz-1, l, r-1)+1LL*getsol(sz-1, l, r)*24%MOD)%MOD);
}

int main(){
  cin>>n;
  cin>>s;
  s='$'+s+"#";
  for(int i=0;i<=n+1;++i){
    for(int j=0;j<=n+1;++j){
      for(int k=0;k<=n+1;++k) dp[i][j][k]=-1;
    }
  } 
  int sol=getsol(n, 1, n);
  assert(sol>=0);
  cout<<sol<<"\n";
  return 0;
}