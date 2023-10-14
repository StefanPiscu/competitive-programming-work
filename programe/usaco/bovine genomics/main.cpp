#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("cownomics.in");
ofstream fout("cownomics.out");

#define MOD 1000000007


int n, m;
int base1=27, base2=29;
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
  long long gethash(int l, int r){
    return (((val1[r]-1LL*val1[l-1]*pow1[r-l+1]%MOD+MOD)%MOD)<<31)^(val2[r]-1LL*val2[l-1]*pow2[r-l+1]%MOD+MOD)%MOD;
  }
};

int main(){
  cin>>n>>m;
  vector<hasher> a(n+1), b(n+1);
  for(int i=1;i<=n;++i){
    string s;
    cin>>s;
    s='$'+s;
    a[i].calchash(s);
  }
  for(int i=1;i<=n;++i){
    string s;
    cin>>s;
    s='$'+s;
    b[i].calchash(s);
  }
  for(int l=1;l<=m;++l){
    for(int j1=1;j1+l-1<=m;++j1){
      int j2=j1+l-1;
      //cout<<j1<<" "<<j2<<"---\n";
      unordered_set<long long> s;
      for(int i=1;i<=n;++i){
       // cout<<(a[i].gethash(j1, j2)>>31)<<" "<<(a[i].gethash(j1, j2)&((1ll<<31)-1))<<"\n";
        s.insert(a[i].gethash(j1, j2));
      }
      bool ok=1;
      for(int i=1;i<=n&&ok;++i){
        if(s.count(b[i].gethash(j1, j2))) ok=0;
      }
      if(ok){
        cout<<l<<"\n";
        return 0;
      }
    }
  }
  assert(0);
  return 0;
}