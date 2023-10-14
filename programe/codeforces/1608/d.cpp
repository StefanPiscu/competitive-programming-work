#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

int fact[100005], inv[100005];

int binpow(int b, int e){
  int sol=1;
  while(e){
    if(e&1) sol=1LL*sol*b%MOD;
    b=1ll*b*b%MOD;
    e>>=1;
  }
  return sol;
}

void getfact(int n=100000){
  fact[0]=1;
  for(int i=1;i<=n;++i) fact[i]=1LL*fact[i-1]*i%MOD;
  inv[n]=binpow(fact[n], MOD-2);
  for(int i=n-1;i;--i){
    inv[i]=1LL*inv[i+1]*(i+1)%MOD;
  }
}

int comb(int n, int k){
  if(n==0||k==0||n==k) return 1;
  return 1LL*(1LL*fact[n]*inv[k]%MOD)*inv[n-k]%MOD;
}

int n;
int nrwl, nrwr, nrbl, nrbr, nrql, nrqr;

int main(){
  getfact();
  cin>>n;
  for(int i=1;i<=n;++i){
    char lc, rc;
    cin>>lc>>rc;
    if(lc=='W') nrwl++;
    else if(lc=='B') nrbl++;
    else nrql++;
    if(rc=='W') nrwr++;
    else if(rc=='B') nrbr++;
    else nrqr++;
  }
  int sol=1;
  if(nrwl<nrwr){
    int val=nrwr-nrwl;
    sol*=comb(nrql, val);
    sol%=MOD;
    nrql -= val, nrwl=nrwr;
  }
  else if(nrwr<nrwl){
    int val=nrwl-nrwr;
    sol*=comb(nrqr, val);
    sol%=MOD;
    nrqr -= val, nrwr=nrwl;
  }
  if(nrbl<nrbr){
    int val=nrbr-nrbl;
    sol*=comb(nrql, val);
    sol%=MOD;
    nrql -= val, nrbl=nrbr;
  }
  else if(nrbr<nrbl){
    int val=nrbl-nrbr;
    sol*=comb(nrqr, val);
    sol%=MOD;
    nrqr -= val, nrbr=nrbl;
  }
  if(nrql<0||nrqr<0){
    cout<<0<<"\n";
    return 0;
  }
  assert(nrql==nrqr);
  int val=0;
  cout<<sol<<" "<<nrql<<"\n";
  if(nrql==0) val=1;
  else{
    for(int i=0;i<=nrql;++i){
      int x=comb(i, nrql);
      val+=(1LL*x*x)%MOD;
      val%=MOD;
    }
  }
  sol*=val;
  sol%=MOD;
  cout<<sol<<"\n";
}