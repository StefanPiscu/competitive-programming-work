#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("dirtraverse.in");
ofstream fout("dirtraverse.out");

#define int long long

struct nod{
  string name;
  int dp;
  int sz;
  int fatsize=3;
  vector<int> out;
};

vector<nod> g;

int n;
int nrl;

void dfs(int x){
  if(g[x].out.size()==0) g[x].sz=1;
  for(auto it:g[x].out){
    dfs(it);
    g[x].dp+=g[it].dp+(g[it].sz*(g[it].name.size()+1));
    g[x].sz+=g[it].sz;
  }
}

int ans=1e18;
void topdown(int x, int dp){
  if(g[x].out.size()==0) return;
  ans=min(ans, dp);
  for(auto it:g[x].out){
    topdown(it, dp-g[it].sz*(g[it].name.size()+1)+(nrl-g[it].sz)*g[it].fatsize);
  }
}

int32_t main(){
  int n;
  cin>>n;
  g.resize(n+1);
  for(int i=1;i<=n;++i){
    cin>>g[i].name;
    int m;
    cin>>m;
    for(int j=1;j<=m;++j){
      int x;
      cin>>x;
      g[i].out.push_back(x);
    }
  } 
  dfs(1);
  nrl=g[1].sz;
  topdown(1, g[1].dp);
  cout<<ans-nrl<<"\n";
}