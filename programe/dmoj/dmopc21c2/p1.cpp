#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, h, p;
int fr[1000002];

int32_t main(){
  cin>>n>>h>>p;
  long long sum=0;
  for(int i=1;i<=n;++i){
    int x;
    cin>>x;
    fr[x]++;
    sum+=x;
  }
  long long sol=(1LL<<60);
  for(int nrh=0;n;nrh++){
    sum-=1LL*nrh*fr[nrh];
    n-=fr[nrh];
    sol=min(sol, 1LL*(sum-nrh*n)*p+1LL*nrh*h);
  }
  cout<<sol<<"\n";
}