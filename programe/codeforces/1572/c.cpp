#include <bits/stdc++.h>
using namespace std;

int n;
int dp[3003][3003];
vector<int> a;
vector<vector<int>> poz;

int main(){
  cin>>n;
  a.resize(n+1);
  poz.resize(n+1);
  for(int i=1;i<=n;++i){
    cin>>a[i];
    poz[a[i]].push_back(i);
  } 
}