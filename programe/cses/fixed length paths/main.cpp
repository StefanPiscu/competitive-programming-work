#include <bits/stdc++.h>
using namespace std;
int n, m;

vector<vector<int>> out;
vector<int> sz, depth, tin, tout;
vector<int> cenfat;
vector<int> closestRed;
vector<bool> remd;
vector<vector<int>> blift;


void setSize(int n){
  out.resize(n+1);
  sz.resize(n+1);
  cenfat.resize(n+1);
  remd.resize(n+1);
  blift.resize(n+1);
  depth.resize(n+1);
  closestRed.resize(n+1, 1e9);
  tin.resize(n+1), tout.resize(n+1);
}

void getsz(int x, int fat=0){
  sz[x]=1;
  for(auto it:out[x]){
    if(it==fat||remd[x]) continue;
    getsz(it, x);
    sz[x]+=sz[it];
  }
}

int timp=0;
void compute(int x, int fat=0){
  if(fat!=0){
    blift[x].push_back(fat);
    int ind=0, cr=fat;
    while(ind<blift[cr].size()){
      blift[x].push_back(blift[cr][ind]);
      ind++;
      cr=blift[x].back();
    }
  }
  tin[x]=++timp;
  for(auto it:out[x]){
    if(it==fat) continue;
    depth[it]=depth[x]+1;
    compute(it, x);
  }
  tout[x]=++timp;
}

bool isanc(int u, int v){
  return tin[u]<=tin[v]&&tout[v]<=tout[u];
}

int msb(int x){
  return 31-__builtin_clz(x);
}

int getlca(int a, int b){
  if(isanc(a, b)) return a;
  if(isanc(b, a)) return b;
  int l=blift[a].size()-1;
  while(l>=0){
    if((l<blift[a].size())&&(!isanc(blift[a][l], b))) a=blift[a][l];
    l--;
  }
  return blift[a][0];
}

int getdist(int a, int b){
  if(a==0||b==0) return 1e9;
  int c=getlca(a, b);
  return depth[a]+depth[b]-2*depth[c];
}


int main(){

}
