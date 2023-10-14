#include <bits/stdc++.h>
using namespace std;

int dx[4]={0, 0,1,-1};
int dy[4]={1,-1,0, 0};

struct solver{
  int n, m, k;
  vector<vector<char>> a;
  vector<vector<int>> dist;
  vector<vector<int>> dist2;

  bool isin(int x, int y){
    return (0<x)&&(x<=n)&&(0<y)&&(y<=m);
  }

  void solve(){
    cin>>n>>m>>k;
    k++;
    a.clear();
    dist.clear();
    dist2.clear();
    a.resize(n+1, vector<char>(m+1));
    dist.resize(n+1, vector<int>(m+1, 0));
    dist2.resize(n+1, vector<int>(m+1, 0));
    queue<pair<int, int>> q;
    queue<pair<int, int>> q2;
    for(int i=1;i<=n;++i){
      for(int j=1;j<=m;++j){
        cin>>a[i][j];
        if(a[i][j]=='.'){
          dist[i][j]=1;
          q.push({i, j});
        }
      }
    }
    while(!q.empty()){
      int x, y;
      tie(x, y)=q.front();
      q.pop();
      assert(dist[x][y]);
      if(dist[x][y]>k) dist2[x][y]=1, q2.push({x, y});
      for(int l=0;l<4;++l){
        int nx=x+dx[l], ny=y+dy[l];
        if((!isin(nx, ny))||dist[nx][ny]) continue;
        dist[nx][ny]=dist[x][y]+1;
        q.push({nx, ny});
      }
    }
    while(!q2.empty()){
      int x, y;
      tie(x, y)=q2.front();
      q2.pop();
      assert(dist2[x][y]);
      for(int l=0;l<4;++l){
        int nx=x+dx[l], ny=y+dy[l];
        if((!isin(nx, ny))||dist2[nx][ny]) continue;
        dist2[nx][ny]=dist2[x][y]+1;
        q2.push({nx, ny});
      }
    }
    for(int i=1;i<=n;++i){
      for(int j=1;j<=m;++j){
        if(a[i][j]=='x'&&dist2[i][j]>k){
          cout<<"NIE\n";
          return;
        }
        if(a[i][j]=='.'&&dist2[i][j]<=k){
          cout<<"NIE\n";
          return;
        }
      }
    }
    cout<<"TAK\n";
  }
};


int main(){
  int t;
  cin>>t;
  while(t--){
    solver x;
    x.solve();
  }
}