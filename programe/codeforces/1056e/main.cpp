#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define int long long

string s;
string t;

int base=29;
vector<int> vals, pows;

void calchash(string s){
  vals.resize(s.size()+2, 0);
  pows.resize(s.size()+2, 1);
  for(int i=1;i<s.size();++i){
    int val=s[i]-'a'+1;
    vals[i]=(1LL*vals[i-1]*base%MOD+val)%MOD;
    pows[i]=(1LL*pows[i-1]*base)%MOD;
  }
}

int gethash(int l, int r){
  return (vals[r]-1LL*vals[l-1]*pows[r-l+1]%MOD+MOD)%MOD;
}

bool iseq(int l1, int r1, int l2, int r2){
  return gethash(l1, r1)==gethash(l2, r2);
}

int32_t main(){
  cin>>s;
  s='$'+s;
  int n=s.size()-1;
  int nr0=0, nr1=0;
  for(int i=1;i<=n;++i)
    if(s[i]=='0') nr0++;
    else nr1++;
  if(nr0<nr1){
    for(int i=1;i<s.size();++i) s[i]='1'-s[i]+'0';
    swap(nr0, nr1);
  }
  cin>>t;
  t='$'+t;
  int m=t.size()-1;
  calchash(t);
  int sol=0;
  for(int s0=1;s0*nr0<m;++s0){
    if((m-s0*nr0)%nr1) continue;
    int s1=(m-s0*nr0)/nr1;
    if(s1==0) continue;
    int p=1, i=1;
    int l0=0, l1=0;
    bool ok=1;
    while(p<=m&&ok){
      if(s[i]=='0'){
        assert((p+s0-1)<=m);
        if(l0==0) l0=p;
        else if(!iseq(l0, l0+s0-1, p, p+s0-1)) ok=0;
        i++, p=p+s0;
      }
      else{
        assert((p+s1-1)<=m);
        if(l1==0) l1=p;
        else if(!iseq(l1, l1+s1-1, p, p+s1-1)) ok=0;
        i++, p=p+s1;
      }
    }
    if(ok) sol++;
  }
  if(m%n==0){
    int ok=1;
    for(int i=m/n+1;i<=m&&ok;i+=m/n){
      if(!iseq(i-m/n, i-1, i, i+m/n-1)) ok=0;
    }
    sol-=ok;
  }
  cout<<sol<<"\n";
}