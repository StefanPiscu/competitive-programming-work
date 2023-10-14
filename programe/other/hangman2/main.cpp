#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int t;
int base=29, base2=31;
vector<int> pows;

struct solver{
  int n, k;
  struct hasher{
  vector<int> val1, val2, pow1, pow2;
  void calchash(string s){
    val1.resize(s.size(), 0);
    val2.resize(s.size(), 0);
    pow1.resize(s.size(), 1);
    pow2.resize(s.size(), 1);
    for(int i=1;i<s.size();++i){
      int val;
      if(s[i]=='A') val=1;
      else if(s[i]=='C') val=2;
      else if(s[i]=='G') val=3;
      else val=4;
      val1[i]=(1LL*val1[i-1]*base1%MOD+val)%MOD;
      val2[i]=(1LL*val2[i-1]*base2%MOD+val)%MOD;
      pow1[i]=1LL*pow1[i-1]*base1%MOD;
      pow2[i]=1LL*pow2[i-1]*base2%MOD;
    }
  }
  int gethash(int l, int r){
    return (((val1[r]-1LL*val1[l-1]*pow1[r-l+1]%MOD+MOD)%MOD))^(val2[r]-1LL*val2[l-1]*pow2[r-l+1]%MOD+MOD)%MOD;
  }
};

  long long combhash(int a, int b, int c){
    return (long long)a^((long long)b<<15)^((long long)c<<30);  
  }

  void solve(){
    cin>>n>>k;
    if(k<n) solvek2();
    else solvek2();
  }
  void solvek2(){
    vector<string> v(n+1);
    vector<hasher> hs(n+1);
    pows.resize(k+1, 1);
    for(int i=1;i<=k;++i) pows[i]=1LL*pows[i-1]*base%MOD;
    for(int i=1;i<=n;++i){
      cin>>v[i];
      v[i]='$'+v[i];
      hs[i].calchash(v[i]);
    }
    vector<int> sol(n+1);
    for(int j1=1;j1<=k;++j1){
      for(int j2=j1;j2<=k;++j2){
        unordered_map<long long, int> mp;
        for(int i=1;i<=n;++i){
          long long x=combhash(hs[i].gethash(1, j1-1), hs[i].gethash(j1+1, j2-1), hs[i].gethash(j2+1, k));
          if(mp.count(x)) sol[mp[x]]=sol[i]=1;
          else mp[x]=i;
        }
      }
    }
    for(int i=1;i<=n;++i) cout<<sol[i];
    cout<<"\n";
  }
  void solven2(){
    vector<string> v(n+1);
    for(int i=1;i<=n;++i){
      cin>>v[i];
      v[i]='$'+v[i];
    }
    vector<int> sol(n+1);
    for(int i1=1;i1<=n;++i1){
      for(int i2=i1+1;i2<=n;++i2){
        int nr=0;
        for(int j=1;j<=k;++j){
          if(v[i1][j]!=v[i2][j]) nr++;
          if(nr>2) break;
        }
        if(nr<=2) sol[i1]=sol[i2]=1;
      }
    }
    for(int i=1;i<=n;++i) cout<<sol[i];
    cout<<"\n";
  }
};

int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>t;
  while(t--){
    solver x;
    x.solve();
  }
}