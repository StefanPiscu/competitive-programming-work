#include <bits/stdc++.h>
using namespace std;

struct nod{
  bool used=0;
  int cost=1e9;
  int last=-1;
  vector<pair<int, int>> out;
};
vector<nod> g;

int main(){
  int n;
  cin>>n;
  g.resize(2*n+2);
  vector<int> a(n+1), b(n+1);
  for(int i=1;i<=n;++i){
    cin>>a[i];
    if(i==a[i]) g[i].out.push_back({0, 1});
    g[i].out.push_back({n+i-a[i], 1});
  }
  for(int i=1;i<=n;++i){
    cin>>b[i];
    g[n+i].out.push_back({i+b[i], 0});
    if(i+1!=n) g[n+i].out.push_back({n+i+1, 0});
  }
  deque<int> q;
  q.push_back(n);
  g[n].cost=0;
  while(!q.empty()){
    int cr=q.front();
    q.pop_front();
    if(g[cr].used) continue;
    g[cr].used=1;
    for(auto it:g[cr].out){
      if(g[it.first].cost<=g[cr].cost+it.second) continue;
      g[it.first].cost=g[cr].cost+it.second;
      if(it.second) q.push_back(it.first);
      else q.push_front(it.first);
      if(cr>n&&it.first<=n) g[it.first].last=cr;
      else g[it.first].last=g[cr].last;
    }
  }
  if(false){
    cout<<g[275980+n].cost<<"\n";
    cout<<b[275980]<<"\n";
    cout<<a[275980+b[275980]]<<"\n";
    cout<<g[214764+n].cost<<"\n";
    cout<<b[214764]<<"\n";
    cout<<a[214764+b[214764]]<<"\n";
    cout<<g[133729+n].cost<<"*\n";
    cout<<g[134325+n].used<<" "<<g[134326+n].used<<"**\n";
    for(int i=133730+n;i<=136524+n;++i){
      if(g[i].cost!=3) cout<<i-n<<" "<<g[i].cost<<"***\n";
    }
    cout<<g[133731+n].cost<<"*\n";
    cout<<g[135424+n].cost<<"\n";
  }
  if(g[0].cost>=1e9){
    cout<<-1<<"\n";
    return 0;
  }
  cout<<g[0].cost<<"\n";
  stack<int> shower;
  int cr=0;
  shower.push(0);
  cr=g[cr].last;
  while(cr!=-1){
    shower.push(cr-n);
    cr=g[cr].last;
  }
  while(!shower.empty()) cout<<shower.top()<<" ", shower.pop();
}