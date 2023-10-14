#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m, x, y, k;
int a[102][102];
int dp[102][102];
int maxi[102][102];
int dx[4]={0,0,-1,1};
int dy[4]={-1,1,0,0};


int32_t main(){
  cin>>n>>m>>x>>y>>k;
  k/=2;
  for(int i=0;i<=n+1;++i){
    for(int j=0;j<=m+1;++j){
      a[i][j]=-1LL<<50;
    }
  }
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      cin>>a[i][j];
      maxi[i][j]=-1LL<<50;
    }
  }
  for(int i=0;i<=n+1;++i){
    for(int j=0;j<=m+1;++j){
      dp[i][j]=-1LL<<50;
    }
  }
  dp[x][y]=0;
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      for(int k=0;k<4;++k){
        maxi[i][j]=max(maxi[i][j], a[i+dx[k]][j+dy[k]]);
      }
      maxi[i][j]+=a[i][j];
    }
  }
  for(int i=x;i<=n;i++){
    for(int j=y;j<=m;j++){
      if(i>x) dp[i][j]=max(dp[i-1][j]+a[i][j]+a[i-1][j], dp[i][j]);
      if(j>y) dp[i][j]=max(dp[i][j-1]+a[i][j]+a[i][j-1], dp[i][j]);
    }
  }
  for(int i=x;i;i--){
    for(int j=y;j<=m;j++){
      if(i<x) dp[i][j]=max(dp[i+1][j]+a[i][j]+a[i+1][j], dp[i][j]);
      if(j>y) dp[i][j]=max(dp[i][j-1]+a[i][j]+a[i][j-1], dp[i][j]);
    }
  }
  for(int i=x;i<=n;i++){
    for(int j=y;j;j--){
      if(i>x) dp[i][j]=max(dp[i-1][j]+a[i][j]+a[i-1][j], dp[i][j]);
      if(j<y) dp[i][j]=max(dp[i][j+1]+a[i][j]+a[i][j+1], dp[i][j]);
    }
  }
  for(int i=x;i;i--){
    for(int j=y;j;j--){
      if(i<x) dp[i][j]=max(dp[i+1][j]+a[i][j]+a[i+1][j], dp[i][j]);
      if(j<y) dp[i][j]=max(dp[i][j+1]+a[i][j]+a[i][j+1], dp[i][j]);
    }
  }
  int sol=-(1LL<<50);
  for(int i=1;i<=n;++i){
    for(int j=1;j<=m;++j){
      for(int l=0;l<4;++l){
        int i2=i+dx[l], j2=j+dy[l];
        int dist1=abs(x-i)+abs(y-j), dist2=abs(x-i2)+abs(y-j2);
        int val=a[i][j]+a[i2][j2];
        if(k>=dist1) sol=max(sol, dp[i][j]+(k-dist1)*val);
        if(k>=dist2) sol=max(sol, dp[i2][j2]+(k-dist2)*val);
      }
    }
  }
  cout<<sol<<"\n";
  return 0;
}