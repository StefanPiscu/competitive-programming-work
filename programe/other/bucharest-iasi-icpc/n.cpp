#include <bits/stdc++.h>
using namespace std;

int n;

struct event{
  int ind;
  int sign;
  int time;
  bool operator<(const event &ot) const{
    return time<ot.time||(time==ot.time&&sign>ot.sign);
  }
};

vector<event> events;
vector<bool> used;

int main(){
  cin>>n;
  used.resize(n+1);
  for(int i=1;i<=n;++i){
    int a, b;
    cin>>a>>b;
    events.push_back({i, 1, a});
    events.push_back({i, -1, b});
  }
  sort(events.begin(), events.end());
  vector<int> open;
  int nr=0;
  for(int i=0;i<events.size();++i){
    auto &it=events[i];
    if(it.sign==1){
      open.push_back(it.ind);
    }
    else{
      if(used[it.ind]) continue;
      else{
        nr++;
        for(auto it2:open) used[it2]=1;
        open.clear();
      }
    }
  }
  cout<<nr<<"\n";
  return 0;
}