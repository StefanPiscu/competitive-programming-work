#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 1000000007

vector<vector<int>> out;
vector<int> tin, tout;
vector<vector<int>> blift;
vector<int> depth;

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

int binpow(int b, int e){
  int sol=1;
  while(e){
    if(e&1) sol=(1LL*sol*b)%MOD;
    b=(1LL*b*b)%MOD;
    e>>=1;
  }
  return sol;
}

int32_t main(){
  int n;
  cin>>n;
  out.resize(n+1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    out[a].push_back(b);
    out[b].push_back(a);
  }
  vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
  for(int i=1;i<=n;++i) dp[0][i]=1;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=n;++j){
      dp[i][j]=0;
      dp[i][j]+=dp[i-1][j]*binpow(2, MOD-2)%MOD;
      dp[i][j]+=dp[i][j-1]*binpow(2, MOD-2)%MOD;
    }
  }
  int nri=0;
  for(int i=1;i<=n;++i){
    depth.clear();
    depth.resize(n+1);
    blift.clear();
    blift.resize(n+1);
    tin.clear();
    tin.resize(n+1);
    tout.clear();
    tout.resize(n+1);
    compute(i);
    for(int j=2;j<=n;++j){
      for(int k=1;k<j;++k){
        if(isanc(j, k)) nri++;
        else{
          int l=getlca(j, k);
          int dlj=depth[j]-depth[l], dlk=depth[k]-depth[l];
          nri=(nri+dp[dlj][dlk])%MOD;
        }
        //cout<<i<<" "<<k<<" "<<j<<" "<<nri<<"\n";
      }
    }
    //cout<<i<<" "<<nri<<"\n";
  }
  cout<<1LL*nri*binpow(n, MOD-2)%MOD<<"\n";
}


