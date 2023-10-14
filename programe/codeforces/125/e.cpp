#include <bits/stdc++.h>
#include "../../debugHeader.h"
using namespace std;

#define int long long

int eps=1e-9;

int cost=0;
vector<int> ans;

int n, m, k;

vector<int> fat, sz;
vector<int> deg;
vector<tuple<int, int, int, int>> edges;

int parent(int x){
  if(x==fat[x]) return x;
  return fat[x]=parent(fat[x]);
}

void join(int a, int b, int c, int ind){
  int oa=a, ob=b;
  a=parent(a), b=parent(b);
  if(a==b) return;
  cost+=c;
  ans.push_back(ind);
  deg[oa]++, deg[ob]++;
  if(sz[a]<sz[b]) swap(a, b);
  fat[b]=a;
  sz[a]+=sz[b];
}

bool mycmp(tuple<int, int, int, int> a, tuple<int, int, int, int> b){
  return get<0>(a)<get<0>(b);
}

void mst(int X){
  ans.clear();
  cost=0;
  for(int i=1;i<=n;++i) fat[i]=i, sz[i]=1, deg[i]=0;
  vector<tuple<int, int, int, int>> e2;
  for(auto it:edges){
    int a, b, ind;
    int c;
    tie(c, a, b, ind)=it;
    if(a==1||b==1){
      c+=X;
    }
    e2.push_back(make_tuple(c, a, b, ind));
  }
  sort(e2.begin(), e2.end(), mycmp);
  for(auto it:e2){
    int a, b, ind;
    int c;
    tie(c, a, b, ind)=it;
    join(a, b, c, ind);
  }
}

int32_t main(){
  cin>>n>>m>>k;
  fat.resize(n+1);
  sz.resize(n+1);
  deg.resize(n+1);
  for(int i=1;i<=n;++i) fat[i]=i, sz[i]=1;
  for(int i=1;i<=m;++i){
    int a, b, c;
    cin>>a>>b>>c;
    edges.push_back(make_tuple(2*c, a, b, i));
  }
  int st=-1e7, dr=1e7, sol=st;
  while(st<=dr){
    int mid=(st+dr)/2;
    mst(mid);
    if(deg[1]>=k) st=mid+1, sol=mid;
    else dr=mid-1;
  }
  mst(sol);
  if(deg[1]!=k){
    cout<<-1<<"\n";
    return 0;
  }
  cout<<ans.size()<<"\n";
  for(auto it:ans) cout<<it<<" ";
  cout<<"\n";
  return 0;
}


