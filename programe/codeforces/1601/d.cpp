#include <bits/stdc++.h>
using namespace std;

int n, p;
vector<int> s, a;

int main(){
  cin>>n>>p;
  int nr=0;
  vector<pair<int, int>> messy, clean;
  for(int i=1;i<=n;++i){
    int x, y;
    cin>>x>>y;
    if(x<p) continue;
    if(y<p) nr++;
    else{
      if(x<y) messy.push_back({y, x});
      else clean.push_back({x, y});
    }
  }
  sort(clean.begin(), clean.end());
  sort(messy.begin(), messy.end());
  int sol=clean.size();
  int poz=0;
  for(auto it:messy){
    while(poz<clean.size()&&clean[poz].first<it.first) p=max(p, clean[poz].second), poz;
    if(it.second>=p) sol++, p=max(p, it.first);
  }
  cout<<sol<<"\n";
}