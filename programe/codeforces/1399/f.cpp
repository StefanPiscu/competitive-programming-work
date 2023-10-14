#include <bits/stdc++.h>
using namespace std;

struct func{
  int a, b;
  bool operator<(const func &ot) const{
    if(a==ot.a) return b>ot.b;
    return a<ot.a;
  }
};

struct Graph{
  int n, m;
  vector<vector<pair<int, int>>> out;
  vector<vector<int>> dp;

  Graph(int _n=0): n(_n){
    out.resize(n+1);
    dp.resize(n+1);
  }

  void addedge(int a, int b, int c){
    out[a].push_back({b, c});
    out[b].push_back({a, c});
  }

  void getdp(){
    dp.resize(n+1, vector<int>(m+1, -1e9));
    dp[1][0]=0;
    for(int dist=1;dist<m;++dist){
      for(int x=1;x<=n;++x){
        dp[x][dist+1]=max(dp[x][dist+1], dp[x][dist]);
        for(auto it:out[x]){
          int cr=it.first, cost=it.second;
          if(dp[cr][dist+1]<dp[x][dist]+cost) dp[cr][dist+1]=dp[x][dist]+cost;
        }
      }
    }
  }

  vector<func> getfuncs(){
    vector<func> vs;
    for(int i=1;i<=n;++i){
      for(auto it:out[i]){
        if(it.first<i) continue;
        vs.push_back({it.second, max(dp[i][m], dp[it.first][m])-it.second*m});
      }
    }
    return vs;
  }
};


int main(){
  Graph g;
  cin>>g.n;
  int m;
  cin>>m;
  g.m=m;
  for(int i=1;i<=m;++i){
    int a, b, c;
    cin>>a>>b>>c;
    g.addedge(a, b, c);
  }
  g.getdp();
  vector<func> funcs=g.getfuncs();
  sort(funcs.begin(), funcs.end());
  int sol=0;
  for(int i=1;i<=min(m, q);++i){
    
  }
}