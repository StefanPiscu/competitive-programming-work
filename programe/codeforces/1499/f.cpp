#include <bits/stdc++.h>
using namespace std;

#define MOD 998244353

int n, k;

struct nod{
  vector<int> out;
  int lmax=0;
  vector<int> dp;
  int dpsum;
};
vector<nod> g;

void predfs(int x, int fat){
  for(auto it:g[x].out){
    if(it==fat) continue;
    predfs(it, x);
    g[x].lmax=max(g[x].lmax, g[it].lmax+1);
  }
  g[x].dp.resize(g[x].lmax+2);
}



void solve(int x, int fat){

  for(int i=1;i<=n;++i){

  }

} 


int main(){
  cin>>n>>k;
  g.resize(n+1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    g[a].out.push_back(b);
    g[b].out.push_back(a);
  }
  predfs(1, 0);
  solve(1, 0);
  cout<<g[1].dpsum<<"\n";
}