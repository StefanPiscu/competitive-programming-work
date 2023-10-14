#include <bits/stdc++.h>
using namespace std;

#define EPS 1e-7

int n;
long double t;
vector<pair<long double, long double>> v;

bool check(long double c){
  long double crt=0;
  for(int i=1;i<=n;++i){
    crt+=(v[i].first/(v[i].second+c));
  }
  return crt<=t;
}

int main(){
  cin>>n>>t;
  v.resize(n+1);
  long double st=-1100000, dr=1100000;
  for(int i=1;i<=n;++i){
    cin>>v[i].first>>v[i].second;
    st=max(st, -v[i].second);
  }
  long double sol=dr;
  while(st<=dr){
    long double mid=(st+dr)/2;
    if(check(mid)) sol=mid, dr=mid-EPS;
    else st=mid+EPS;
  }
  cout<<fixed<<setprecision(10)<<sol<<"\n";
}