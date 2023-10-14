#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MOD 1000000007

vector<int> bases;
vector<int> vals;
vector<int> pows;

bool operator<(const vector<int> a, const vector<int> b){
  int sz=min(a.size(), b.size());
  for(int i=0;i<sz;++i){
    if(a[i]<b[i]) return 1;
    else if(b[i]<a[i]) return 0;
  }
  if(a.size()<b.size()) return 1;
  return 0;
}

set<vector<int>> seen;

string s;
int fr[27];

int32_t main(){
  srand(time(0));
  bases.resize(2);
  for(int i=0;i<bases.size();++i){
    bases[i]=rand();
  }
  vals.resize(2, 0);
  pows.resize(2, 1); 
  string h;
  cin>>h;
  for(auto it:h) fr[it-'a']++;
  cin>>s;
  if(h.size()>s.size()){
    cout<<"0\n";
    return 0;
  }
  int frc[27]={0};
  for(int i=0;i<h.size();++i){
    int val=s[i]-'a';
    frc[val]++;
    for(int i=0;i<bases.size();++i){
      vals[i]=(bases[i]*vals[i]%MOD+val)%MOD;
      pows[i]=pows[i]*bases[i]%MOD;
    }
  }
  bool ok=1;
  for(int i=0;i<26;++i){
    if(fr[i]!=frc[i]) ok=0;
  }
  if(ok){
    seen.insert(vals);
  }
  for(int i=h.size();i<s.size();++i){
    int val=s[i]-'a', lval=s[i-h.size()]-'a';
    frc[val]++;
    frc[lval]--;
    for(int i=0;i<bases.size();++i){
      vals[i]=(bases[i]*vals[i]%MOD+val-(pows[i]*lval%MOD)+MOD)%MOD;
    }
    bool ok=1;
    for(int i=0;i<26;++i){
      if(fr[i]!=frc[i]) ok=0;
    }
    if(ok){
      seen.insert(vals);
    }
  }
  cout<<seen.size()<<"\n";
  return 0;
}