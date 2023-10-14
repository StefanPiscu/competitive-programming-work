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


int getcent(int x, int fat, const int n){
  for(auto it:out[x]){
    if(it==fat||remd[it]) continue;
    if(sz[it]>((n-1)/2)) return getcent(it, x, n);
  }
  return x;
}

void getcenttree(int root, int fat=0){
  getsz(root);
  root=getcent(root, -1, sz[root]);
  remd[root]=1;
  cenfat[root]=fat;
  for(auto it:out[root]){
    if(remd[it]) continue;
    getcenttree(it, root);
  }
}

void makeRed(int x){
  int crdist=0, cr=x;
  while(cr){
    closestRed[cr]=min(getdist(cr, x), closestRed[cr]);
    cr=cenfat[cr];
  }
}

int getClosestRed(int x){
  int cr=x;
  int bestRed=1e9;
  while(cr){
    bestRed=min(bestRed, closestRed[cr]+getdist(cr, x));
    cr=cenfat[cr];
  }
  return bestRed;
}

int main(){
  cin>>n>>m;
  setSize(n);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    out[a].push_back(b);
    out[b].push_back(a);
  }
  compute(1);
  getcenttree(1);

/*
  for(int i=1;i<=n;++i){
    cout<<i<<" "<<cenfat[i]<<"****\n";
  }
*/
  

  makeRed(1);
/*
  cout<<getlca(1, 10)<<"\n";
  cout<<getdist(1, 10)<<"\n";
*/
  while(m--){
    int a, b;
    cin>>a>>b;
    if(a==1){
      makeRed(b);
    }
    else{
      cout<<getClosestRed(b)<<"\n";
    }
  }
  return 0;
}
