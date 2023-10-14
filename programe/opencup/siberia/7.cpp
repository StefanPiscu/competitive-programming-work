#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

long double dp[3][200002];
long double mini[200002];
int sol[200002];

long double myabs(long double x){
  return max(x, -x);
}

int main(){
  int t;
  int c=200002;
  for(int i=1;i<=352;++i){
    int l=i%2, ll=1-l;
    //cout<<i<<" "<<l<<" "<<ll<<endl;
    for(int j=0;j+i<=c;++j){

      if(j<i) dp[l][j]=1;
      else{
        dp[l][j]=0;
        if(j-1<i-1) dp[l][j]+=(i/double(i+j));
        else dp[l][j]+=(i/double(i+j))*dp[ll][j-1];
        if(j-2<i)  dp[l][j]+=(j/double(i+j));
        else dp[l][j]+=(j/double(i+j))*dp[l][j-2];
        if(myabs(0.5-mini[i+j])>myabs(0.5-dp[l][j])) mini[i+j]=dp[l][j], sol[i+j]=i;
      }
    }
  }
  cin>>t;
  while(t--){
    int x;
    cin>>x;
    cout<<sol[x]<<"\n";
  }
}