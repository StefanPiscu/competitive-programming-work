#include <bits/stdc++.h>
using namespace std;

struct solver{
  int n, m;
  int dp[404][404];

  int getval(int x1, int y1, int x2, int y2){
    return dp[x2][y2]-dp[x1-1][y2]-dp[x2][y1-1]+dp[x1-1][y1-1];
  }
  int getcost(int x1, int y1, int x2, int y2){
    int costinterior=getval(x1+1, y1+1, x2-1, y2-1);
    int costlinii=2*(y2-y1-1)-getval(x1, y1+1, x1, y2-1)-getval(x2, y1+1, x2, y2-1);
    int costcoloane=2*(x2-x1-1)-getval(x1+1, y1, x2-1, y1)-getval(x1+1, y2, x2-1, y2);
    return costinterior+costlinii+costcoloane;
  }
  
  void solve(){
    cin>>n>>m;
    for(int i=1;i<=n;++i){
      for(int j=1;j<=m;++j){
        char x;
        cin>>x;
        dp[i][j]=0;
        if(x=='1') dp[i][j]++;
        dp[i][j]+=dp[i-1][j]+dp[i][j-1]-dp[i-1][j-1];
      }
    }
    int sol=1e9;
    for(int i1=1;i1+4<=n;++i1){
      for(int i2=i1+4;i2<=n;++i2){
        int bestj=1;
        for(int j=4;j<=m;++j){
          if(getcost(i1, bestj, i2, j)>getcost(i1, j-3, i2, j)) bestj=j-3;
          sol=min(sol, getcost(i1, bestj, i2, j));
        }
      }
    }
    cout<<sol<<"\n";
  }
};

int main(){
  int t;
  cin>>t;
  while(t--){
    solver x;
    x.solve();
  }  
  return 0;
}