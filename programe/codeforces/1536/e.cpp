#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 1000000007

int binpow(int b, int e){
  int sol=1;
  while(e){
    if(e&1) sol=sol*b%MOD;
    b=b*b%MOD;
    e>>=1;
  }
  return sol;
}

struct solver{
  int n, m;

  void solve(){
    cin>>n>>m;
    int nr=0;
    for(int i=1;i<=n;++i){
      for(int j=1;j<=m;++j){
        char x;
        cin>>x;
        if(x=='#') nr++;
      }
    }
    int sol=binpow(2, nr);
    if(nr==n*m) sol--;
    sol=(sol+MOD)%MOD;
    cout<<sol<<"\n";
  }

};

int32_t main(){
  int n;
  cin>>n;
  while(n--){
    solver mySolver;
    mySolver.solve();
  }
  return 0;
}