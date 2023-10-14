#include <bits/stdc++.h>
using namespace std;

//#define DEBUG

int n, m;
int a[102][102];
int b[102][102];
int used[102][102];

inline bool isin(int x, int y){
  return (0<x)&&(x<=n)&&(0<y)&&(y<=m);
}
int dx[4]={0,0,1,-1};
int dy[4]={1,-1,0,0};

class MaxFlow{
private:
  int const inf = 1000000000;
  struct Edge{
    int to;
    int rev;
    int flow;
    int cap;
  };
  int n;
  std::vector<std::vector<Edge>> g;
  std::vector<int> level, rem;
  int source;
  int sink;
public:
  MaxFlow(int n_) {
    n = n_;
    source = 0;
    sink = n - 1;
    
    g.resize(n);
    level.resize(n);
    rem.resize(n);
  }
  void addEdge(int x, int y, int cap) {
    #ifdef DEBUG
    cout<<x<<" "<<y<<"\n";
    #endif
    g[x].push_back({y, g[y].size(), 0, cap});
    g[y].push_back({x, g[x].size() - 1, 0, 0});
  }
  void setSourceSink(int _source, int _sink) {
    source = _source;
    sink = _sink;
  }
  bool BFS() {
    for(int i = 0; i < n; i++)
      level[i] = -1;
    std::queue<int> q;
    level[source] = 0;
    q.push(source);
    while(0 < q.size()) {
      int node = q.front();
      q.pop();
      for(int h = 0; h < g[node].size(); h++) {
        Edge e = g[node][h];
        if(e.flow < e.cap && level[e.to] == -1) {
          level[e.to] = level[node] + 1;
          q.push(e.to);
        }
      }
    }
    return 0 <= level[sink];
  }
  int DFS(int node, int delta) {
    if(node == sink)
      return delta;
    else {
      for(int &h = rem[node]; h < g[node].size(); h++) {
        Edge &e = g[node][h]; 
        if(e.flow < e.cap && level[node] + 1 == level[e.to]) {
          int deltaflow = DFS(e.to, std::min(delta, e.cap - e.flow));
          if(0 < deltaflow) {
            e.flow += deltaflow;
            g[e.to][e.rev].flow -= deltaflow;
            return deltaflow;
          }
        }
      }
      return 0;
    }
  }
  int64_t maxflow() {
    int64_t result = 0, delta = 0;
    while(BFS()) {
      for(int i = 0; i < n; i++)
        rem[i] = 0;
      delta = 0;
      do {
        result += delta;
        delta = DFS(source, inf);
      } while(0 < delta);
    }
    return result;
  }
};

int main(){
  cin>>n>>m;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      char x;
      cin>>x;
      if(x=='0') a[i][j]=0;
      else a[i][j]=1;
    }
  }
  int val=0;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      char x;
      cin>>x;
      if(x=='0') b[i][j]=0;
      else b[i][j]=1;
      val+=(b[i][j]==a[i][j]);
    }
  }
  int nr=0;
  vector<int> left, right;
  set<pair<int, int>> myEdges;
  vector<int> balances;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      if(used[i][j]) continue;
      nr++;
      int color=a[i][j];
      queue<pair<int, int>> q;
      int bal=0;
      q.push({i, j});
      if(a[i][j]==b[i][j]) bal--;
      else bal++;
      used[i][j]=nr; 
      while(!q.empty()){
        int crx, cry;
        tie(crx, cry)=q.front();
        q.pop();
        for(int k=0;k<4;++k){
          int nx=crx+dx[k], ny=cry+dy[k];
          if(!isin(nx, ny)) continue;
          if(!used[nx][ny]&&a[nx][ny]==color){
            q.push({nx, ny});
            if(a[nx][ny]==b[nx][ny]) bal--;
            else bal++;
            used[nx][ny]=nr; 
          }
          else if(used[nx][ny]!=nr&&used[nx][ny]!=0){
            if(color) myEdges.insert({used[nx][ny]-1, nr-1});
            else myEdges.insert({nr-1, used[nx][ny]-1});
          }
        }
      }
      if(color==0) left.push_back(nr-1);
      else right.push_back(nr-1);
      balances.push_back(bal);
    }  
  }
  #ifdef DEBUG
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      cout<<used[i][j]-1<<" ";
    }
    cout<<"\n";
  }
  for(auto it:myEdges) cout<<it.first<<" "<<it.second<<"\n";
  cout<<"\n";
  for(auto it:left) cout<<it<<" "<<balances[it]<<"\n";
  cout<<"\n";
  for(auto it:right) cout<<it<<" "<<balances[it]<<"\n";
  cout<<"\n";
  #endif
  MaxFlow solver(nr+2);
  solver.setSourceSink(nr, nr+1);
  for(auto it:myEdges){
    if(balances[it.first]<=0||balances[it.second]<=0) continue;
    solver.addEdge(it.first, it.second, 1e9);
  }
  int total=0;
  for(auto it:left){
    if(balances[it]<=0) continue;
    solver.addEdge(nr, it, balances[it]);
    total+=balances[it];
  }
  for(auto it:right){
    if(balances[it]<=0) continue;
    solver.addEdge(it, nr+1, balances[it]);
    total+=balances[it];
  }
  int flow=solver.maxflow();
  assert(flow>=0);
  cout<<n*m-(val+(total-flow))<<"\n";
  return 0;
}
