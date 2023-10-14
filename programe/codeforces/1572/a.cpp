#include <bits/stdc++.h>
using namespace std;

struct nod{
  int val;
  int in;
  vector<int> out;
  bool operator<(const nod &ot) const{
    return val<ot.val; 
  }
};

vector<nod> g;

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    int n;
    cin>>n;
    g.clear();
    g.resize(n+1);
    for(int i=1;i<=n;++i){
      int k;
      cin>>k;
      for(int j=1;j<=k;++j){
        int x;
        cin>>x;
        g[x].out.push_back(i);
        g[i].in++;
      }
    }
    set<int> understandable;
    for(int i=1;i<=n;++i){
      if(g[i].in==0) understandable.insert(i);
    }
    int last=0;
    int nr=0, sol=1;
    while(!understandable.empty()){
      auto it=understandable.upper_bound(last);
      if(it==understandable.end()) last=0, sol++;
      else{
        last=*it;
        understandable.erase(it);
        for(auto it2:g[last].out){
          g[it2].in--;
          if(g[it2].in==0) understandable.insert(it2);
        }
        nr++;
      }
    }
    if(nr==n) cout<<sol<<"\n";
    else cout<<"-1\n";
  }
};