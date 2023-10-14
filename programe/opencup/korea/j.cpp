#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;

int32_t main(){
  cin>>n;
  vector<pair<int, int>> v(n+1);
  for(int i=1;i<=n;++i){
    cin>>v[i].first>>v[i].second;
  }
  sort(v.begin()+1, v.end());
  vector<bool> info(n+1, 0);
  for(int i=1;i<=n;++i){
    vector<bool> fr(i+1, 0);
    int cnt=0;
    for(int j=1;j<=n;++j){
      int x=(1000000000*n+v[j].first)%i;
      if(!fr[x]) fr[x]=1, cnt++;
    }
    if(cnt==i) info[i]=1;
  }
  vector<bool> used(n+1, 0);
  int nr=0, sum=0;
  vector<int> sols;
  for(int i=1;i<=n;++i){
    for(int j=i+1;j<=n;++j){
      if(v[i].second!=v[j].second){
        int dif=v[j].first-v[i].first;
        for(int d=1;d*d<=dif;++d){
          if(dif%d) continue;
          int d2=dif/d;
          if(d<=n) used[d]=1;
          if(d2<=n) used[d2]=1;
          if(d==d2) sols.push_back(d);
          else sols.push_back(d2), sols.push_back(d);
        }
      }
    }
  }
  for(int i=1;i<=n;++i){
    if(!used[i]&&info[i]){
      for(int j=i+i;j<=n;j+=i){
        if(!used[j]&&info[j]) used[j]=1, sols.push_back(j);
      }
    }
  }
  sort(sols.begin(), sols.end());
  sols.resize(unique(sols.begin(), sols.end())-sols.begin());
  for(auto it:sols) nr++, sum+=it;
  cout<<nr<<" "<<sum<<"\n";
}