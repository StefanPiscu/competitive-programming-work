#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, fa, fb;

struct task{
  int a, b, t;
  int ind=0;
  bool operator<(const task &ot) const{
    return t<ot.t;
  }
};
vector<task> v;
vector<int> finsol;

bool check(int d){
  int cost=fa;
  int suma=0, sumb=0, mini=1e9;
  int last=1;
  finsol.clear();
  for(int i=1;i<=n;++i){
    suma+=v[i].a;
    sumb+=v[i].b;
    mini=min(mini-v[i].a, v[i].t-(suma+sumb+cost+fb));
    if((-mini)>d){
      cost+=suma-v[i].a+sumb-v[i].b+fb+fa;
      suma=v[i].a, sumb=v[i].b;
      mini=v[i].t-suma-sumb-fb-cost;
      if((-mini)>d){
        return 0;
      }
      for(int j=last;j<i;++j){
        finsol.push_back(-v[j].ind);
      }
      for(int j=last;j<i;++j){
        finsol.push_back(v[j].ind);
      }
      last=i;
    }
  }
  for(int j=last;j<=n;++j){
    finsol.push_back(-v[j].ind);
  }
  for(int j=last;j<=n;++j){
    finsol.push_back(v[j].ind);
  }
  return 1;
}

int32_t main(){
  cin>>n>>fa>>fb;
  int st=0, dr=0;
  v.resize(n+1);
  for(int i=1;i<=n;++i){
    cin>>v[i].a>>v[i].b>>v[i].t;
    v[i].ind=i;
    dr+=(fa+v[i].a+fb+v[i].b);
  }
  sort(v.begin(), v.end());
  int sol=dr;
  while(st<=dr){
    int mid=(st+dr)/2;
    if(check(mid)) sol=mid, dr=mid-1;
    else st=mid+1; 
  }
  check(sol);
  cout<<sol<<"\n";
  for(auto it:finsol) cout<<it<<" ";
  return 0;
}
