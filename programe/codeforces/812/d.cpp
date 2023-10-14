#include <bits/stdc++.h>
using namespace std;

int n, m, k, q;

struct nod{
  int tin, tout;
  int sz;
  vector<int> out;
};

int timp=0;
vector<nod> g;

void dfsinit(int x, int fat){
  g[x].sz=1;
  g[x].tin=(++timp);
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfsinit(it, fat);
    g[x].sz+=g[it].sz;
  }
  g[x].tout=(++timp);
}

bool isanc(nod a, nod b){
  return a.tin<=b.tin&&b.tout<=a.tout;
}

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>n>>m>>k>>q;  
  g.resize(n+1);
  vector<int> owners(m+1);
  for(int i=1;i<=k;++i){
    int a, b;
    cin>>a>>b;
    if(owners[b]){
      g[owners[b]].out.push_back(a);
      owners[b]=a;
    }
    else owners[b]=a;
  }
  for(int i=1;i<=n;++i) if(!g[i].tin) dfsinit(i, 0);
  for(int i=1;i<=q;++i){
    int a, b;
    cin>>a>>b;
    int c=owners[b];
    // owners[b] -> a;
    assert(a<=n&&c<=n);
    if(isanc(g[a], g[c])) cout<<g[a].sz<<"\n";
    else cout<<0<<"\n";
    cout.flush();
  }
  return 0;
}