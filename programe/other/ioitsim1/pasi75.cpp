#include <bits/stdc++.h>
using namespace std;

#define int long long

int dx[4]={-1, 1, 0, 0};
int dy[4]={0, 0, -1, 1};
int a[103][103];

struct state{
  int x, y;
  int dist, sol;
};


int32_t main(){
  int n, m, x, y, k;
  cin>>n>>m>>x>>y>>k;
  for(int i=0;i<=n+1;++i){
    for(int j=0;j<=m+1;++j){
      a[i][j]=-1LL<<50;
    }
  }
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      cin>>a[i][j];
    }
  }
  k/=2;
  queue<state> q;
  q.push({x, y, 0, 0});
  int sol=0;
  vector<vector<bool>> used(n+1, vector<bool>(m+1, 0));
  used[x][y]=1;
  int last=0;
  while(!q.empty()){
    state cr=q.front();
    cout<<cr.x<<" "<<cr.y<<" "<<cr.dist<<"\n";
    q.pop();
    if(cr.dist!=last){
      last=cr.dist;
      used.resize(n+1, vector<bool>(m+1, 0));
    }

    if(cr.dist==k) sol=max(sol, cr.sol); 
    else{
      for(int l=0;l<4;++l){
        int nx=cr.x+dx[l], ny=cr.y+dy[l];
        if(nx<=0||n<nx||ny<=0||m<ny||used[nx][ny]) continue;
        int val=a[cr.x][cr.y]+a[nx][ny];
        q.push({nx, ny, cr.dist+1, val+cr.sol});
        used[nx][ny]=1;
      }
    }
  }
  cout<<sol<<"\n";
}
