#incude <bits/stdc++.h>
using namespace std;



struct solution{
  int n;
  vector<pair<int, int>> p;
  void solve(){
    cin>>n;
    p.resize(n+1);
    for(int i=1;i<=n;++i){
      cin>>p[i].first;
    }
    for(int i=1;i<=n;++i){
      cin>>p[i].second;
    }

    vector<pair<int, int>> pcts;
    for(int i=1;i<=n;++i){
      for(int j=1;j<=n;++j){
        int x1=p[i].first*2, y1=p[i].second*2, x2=p[j].first*2, y2=p[j].second*2;
        pcts.push_back({(x1+y1+x2-y2)/2, (x1+y1+y2-x2)/2});
        pcts.push_back({x1+y1-y2, y2});
        pcts.push_back({x2, x1+y1-y2});
        pcts.push_back({x1-y1+y2, y2});
        pcts.push_back({x2, x1-y1+y2});
        pcts.push_back({x1, y2});
      }
    }
    int ans=1e9;
    for(auto it:pcts){
      int x=it.first, y=it.second;
      int sol=0;
      for(int i=1;i<=n;++i){
        int xt=p[i].first*2, yt=p[i].second*2;
        if(x==xt&&y==yt) continue;
        if(xt==x||yt==y||abs((xt-x))==abs((yt-y))) sol++;
        else sol+=2;
      }
      ans=min(ans, sol);
    }
    cout<<ans<<"\n";
  }
};

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    solution x;
    x.solve();
  }
}