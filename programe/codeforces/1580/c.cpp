#include <bits/stdc++.h>
using namespace std;

struct train{
  int x, y;
  int l, r;
};

int n, m;
int sq;
vector<train> trains;
vector<vector<train>> trains_with_per; //holds trains with a certain period
vector<int> ans; 

int main(){
  cin>>n>>m;
  sq=sqrt(m);
  vector<pair<int, int>> xys;
  trains_with_per.resize(sq+1);
  ans.resize(m+2);
  xys.resize(n+1);
  for(int i=1;i<=n;++i){
    cin>>xys[i].first>>xys[i].second;
  }
  vector<int> open(n+1);
  for(int i=1;i<=m;++i){
    int op, k;
    cin>>op>>k;
    if(op==1) open[k]=i;
    else trains.push_back({xys[k].first, xys[k].second, open[k], i}), open[k]=0;
  }
  for(int i=1;i<=n;++i){
    if(open[i]) trains.push_back({xys[i].first, xys[i].second, open[i], m+1});
  }
  for(auto it:trains){
    if(it.x+it.y<=sq){
      trains_with_per[it.x+it.y].push_back(it);
    }
    else{
      for(int poz=it.l+it.x;poz<it.r;poz+=it.x+it.y){
        ans[poz]++;
        if(poz+it.y<=it.r) ans[poz+it.y]--;
        else ans[it.r]--;
      }
    }
  }
  for(int per=1;per<=sq;++per){
    vector<int> val(m+2, 0);
    for(auto it:trains_with_per[per]){
      int l=it.l+it.x;
      int r=l+ceil((it.r-l)/(double)per)*per;
      assert((r-per)<it.r);
      assert((r-l)%per==0);
      //cout<<l<<" "<<r<<endl;
      if(l>it.r) continue;
      if(l<=m) val[l]++;      
      if(r<=m) val[r]--;

      l=it.l+per;
      r=l+ceil((it.r-l)/(double)per)*per;
      assert((r-per)<it.r);
      assert((r-l)%per==0);
      //cout<<l<<" "<<r<<endl;
      if(l>it.r) continue;
      if(l<=m) val[l]--;
      if(r<=m) val[r]++;
    }
    //cout<<per<<"\n";
    for(int i=1;i<=m;++i){
      //cout<<val[i]<<" ";

      if(i>per) val[i]+=val[i-per];
      ans[i]+=val[i];
    }
    //cout<<"\n";
  }
  for(int i=1;i<=m;++i){
    ans[i]+=ans[i-1];
    cout<<ans[i]<<"\n";
  }

}