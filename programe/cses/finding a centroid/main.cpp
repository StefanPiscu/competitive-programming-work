#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> out;
vector<bool> used;
vector<int> sz;

void addedge(int a, int b){
  out[a].push_back(b);
  out[b].push_back(a);
}

void calcsz(int x, int fat){
  sz[x]=1;
  for(auto it:out[x]){
    if(it==fat||used[it]) continue;
    calcsz(it, x);
    sz[x]+=sz[it];
  }
}

int findcentroid(int x, int fat, const int &sztot){
  for(auto it:out[x]){
    if(it==fat||used[it]) continue;
    if(sz[it]>sztot/2) return findcentroid(it, x, sztot);
  }
  return x;
}

int main(){
  cin>>n;
  out.resize(n+1);
  sz.resize(n+1);
  used.resize(n+1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    addedge(a, b);
  }
  calcsz(1, 0);
  cout<<findcentroid(1, 0, n)<<"\n";
}