#pragma GCC optimize ("Ofast")
#include <bits/stdc++.h>
using namespace std;


int n, m, k, p;
int comb[102][102];
int fac[102];
int memo[102][102][102];

void getmath(int n=101){
  comb[1][0]=1, comb[1][1]=1;
  fac[0]=1;
  for(int i=1;i<=n;++i) fac[i]=1LL*fac[i-1]*i%p;
  for(int i=2;i<=n;++i){
    comb[i][0]=1;
    for(int j=1;j<=i;++j){
      comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
      comb[i][j]%=p;
    }
  }
}

void dp(int n, int m, int k){
  //cout<<n<<" "<<m<<" "<<k<<"*"<<endl;
  if(memo[n][m][k]>=0) return;
  if(k==0&&m>n) memo[n][m][k]=fac[n];
  else if(m==1) memo[n][m][k]=0;
  else if(m>n||k>n) memo[n][m][k]=0;
  else{
    int val=0;
    for(int k1=0;k1<=n-1;++k1){
      int bnd=min(k-1, max({3, k1, (n-1-k1)}));
      for(int k2=0;k2<=bnd;++k2){
        dp(n-1-k1, m-1, k-k2);
        dp(k1, m-1, k2);
        val+=1LL*comb[n-1][k1]*memo[n-1-k1][m-1][k-k2]%p*memo[k1][m-1][k2]%p;
        val%=p;
      }
      dp(n-1-k1, m-1, 0);
      dp(k1, m-1, k);
      val+=1LL*comb[n-1][k1]*memo[n-1-k1][m-1][0]%p*memo[k1][m-1][k]%p;
      val%=p;

    }
    //cout<<n<<" "<<m<<" "<<k<<" "<<val<<endl;
    memo[n][m][k]=val;
  }
}



int32_t main(){
  cin>>n>>m>>k>>p;
  getmath(n+1);
  memset(memo, -1, sizeof(memo));
  for(int i=0;i<=m;++i) memo[0][i][0]=1;
  for(int i=1;i<=n;++i) memo[i][1][1]=fac[i];
  dp(n, m, k);
  cout<<memo[n][m][k]<<"\n";
}