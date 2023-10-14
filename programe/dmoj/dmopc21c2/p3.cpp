#include <bits/stdc++.h>
using namespace std;

#define int long long

int nrg=0;

void solve(){
  nrg++;
  if(nrg>32000) assert(0);
  cout<<0<<endl;
  int n, m;
  cin>>n;
  if(n==0){
    return;
  }
  if(n==1){
    nrg++;
    if(nrg>32000) assert(0);
    cout<<1<<endl;
    int resp;
    cin>>resp;
    if(resp==-1) exit(0);
    if(resp==0) return;
    assert(0);
  }
  m=n-1;
  int y=1LL<<(n-1);
  while(true){
    y^=(1LL<<(m-1));
    for(int i=0;i<(m-1);++i){
      int x=rand()&1;
      y^=(x<<i);
    }
    nrg++;
    if(nrg>32000) assert(0);
    cout<<y<<endl;
    int resp;
    cin>>resp;
    if(resp==-1) exit(0);
    if(resp==0) return;
    assert(resp%2==0);
    m=resp/2;
  }
}

int32_t main(){
  srand(time(0));
  int n;
  cin>>n;
  while(n--) solve();
}