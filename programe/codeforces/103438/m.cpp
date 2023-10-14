#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define COMBI 0
int MOD=0;

int N;
vector<int> solution;

int binpow(int b, int e){
  int sol=1;
  while(e){
    if(e&1) sol=1LL*sol*b%MOD;
    b=1LL*b*b%MOD;
    e>>=1;
  }
  return sol;
}

int fact[500007], inv[500007];

void getfact(int n=500006){
  fact[0]=1;
  for(int i=1;i<=n;++i) fact[i]=1LL*fact[i-1]*i%MOD;
  inv[n]=binpow(fact[n], MOD-2);
  for(int i=n-1;i;--i){
    inv[i]=1LL*inv[i+1]*(i+1)%MOD;
  }
}

int comb(int n, int k){
  if(n==0||k==0||(n==k)) return 1;
  return ((1LL*((1LL*fact[n]*inv[k])%MOD)*inv[n-k])%MOD);
}

void solve(int sum, int pro, int n, int current, int value, bool changed=1){
  if((pro-sum)>(N-n)) return;
  if(changed){
    solution[n+(pro-sum)]+=1LL*value*comb(n+(pro-sum), n)%MOD;
    solution[n+(pro-sum)]%=MOD;
    for(int current2=current+1;current2<=N;++current2){
      if((1LL*pro*current2)-(sum+current2)>1LL*(N-(n+1))) break;
      solve(sum, pro, n, current2, value, 0);
    }
  }
  int nsum=sum, npro=pro;
  for(int nr=1;n+nr<=N;nr++){
    nsum+=current;
    if((1LL*npro*current-nsum)>(N-(n+nr))) break;
    npro*=current;
    solve(nsum, npro, n+nr, current+1, 1LL*value*comb(n+nr, n)%MOD, 1);
  }
}

int32_t main(){
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  cin>>N>>MOD;
  solution.resize(N+8);
  getfact();
  solve(0, 1, 0, 2, 1);
  for(int i=2;i<=N;++i) cout<<solution[i]<<" ";
  cout<<"\n";
  return 0;
}