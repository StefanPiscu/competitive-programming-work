#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m;
unordered_map<int, vector<pair<int, int>>> xs;

void add(int x, int y, int r){
  int dx=floor(cbrt(r));
  int lx=max(0ll, x-dx), rx=min(n, x+dx);
  //cout<<x<<" "<<y<<" "<<r<<"****\n";
  for(int crx=lx;crx<=rx;++crx){
    int spr=r-abs(crx-x)*abs(crx-x)*abs(crx-x);
    int dy=floor(cbrt(spr));
    int ly=max(0ll, y-dy), ry=min(n, y+dy);
    //cout<<crx<<" "<<ly<<" "<<ry<<"\n";
    xs[crx].push_back({ly, ry});
  }
}

int32_t main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=m;++i){
    int a, b, c;
    cin>>a>>b>>c;
    add(a, b, c);
  }
  int sol=0;
  for(auto it:xs){
    int last=-1;
    sort(it.second.begin(), it.second.end());
    //cout<<it.first<<"\n";
    for(auto it2:it.second){
      int a=it2.first, b=it2.second;
      if(a<=last) a=last+1;
      sol+=max(0ll, (b-a+1));
      //cout<<a<<" "<<b<<" "<<sol<<"\n";
      if(b>last) last=b;
    }
  }
  cout<<(n+1)*(n+1)-sol<<"\n";
  return 0;
}