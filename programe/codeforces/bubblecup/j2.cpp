#include <bits/stdc++.h>
using namespace std;

unsigned int getnext(unsigned int v){
  unsigned int w;
  unsigned int t=v|(v-1); 
  w=(t+1)|(((~t&-~t)-1)>>(__builtin_ctz(v)+1));
  return w;
}


int main(){
  int n;
  cin>>n;
  vector<int> v(n+1);
  for(int i=1;i<=n;++i) cin>>v[i];
  vector<int> par, imp;
  map<int, int> fr;
  for(int i=1;i<=n;++i){
    if(fr.count(v[i])){
      int p1=fr[v[i]], p2=i;
      cout<<"YES\n";
      cout<<0<<" "<<v[i]<<" ";
      for(int i=1;i<=n;++i){
        if(i==p1||i==p2) continue;
        cout<<v[i]<<" ";
      }
      cout<<"\n";
      return 0;
    }
    fr[v[i]]=i;
    if(v[i]%2){
      imp.push_back(i);
      if(imp.size()>=2&&par.size()){
        cout<<"YES\n";
        int sum=(v[imp[0]]+v[imp[1]]+v[par[0]])/2;
        int a=sum-v[imp[0]], b=sum-v[imp[1]], c=sum-v[par[0]];
        cout<<a<<" "<<b<<" "<<c<<" ";
        for(int i=1;i<=n;++i){
          if(i==imp[0]||i==imp[1]||i==par[0]) continue;
          cout<<v[i]-a<<" ";
        }
        cout<<"\n";
        return 0;
      }
    }
    else{
      par.push_back(i);
      if(par.size()>=3){
        cout<<"YES\n";
        int sum=(v[par[0]]+v[par[1]]+v[par[2]])/2;
        int a=sum-v[par[0]], b=sum-v[par[1]], c=sum-v[par[2]];
        cout<<a<<" "<<b<<" "<<c<<" ";
        cout.flush();
        for(int i=1;i<=n;++i){
          if(i==par[0]||i==par[1]||i==par[0]) continue;
          cout<<v[i]-a<<" ";
        }
        cout<<"\n";
        return 0;
      }
    }
  }
  int sz=0;
  vector<int> a, b;
  int solmask=0;
  int ok=0;
  if(n<26){
    vector<int> mp(14000002);
    for(int k=2;k<=min(13, n/2);++k){
      int mask=(1<<k)-1; 
      while(mask<(1<<n)){
        int sum1=0;
        for(int i=1;i<=n;++i){
          if(mask&(1<<(i-1))) sum1+=v[i];
        }
        if(mp[sum1]!=0){
          int mask1=mask, mask2=mp[sum1];
          mask1=mask1^(mask1&mask2);
          mask2=mask2^(mask1&mask2);
          for(int i=1;i<=n;++i){
            if(mask1&(1<<(i-1))) a.push_back(v[i]);
            else if(mask2&(1<<(i-1))) b.push_back(v[i]);
          }
          solmask=mask1^mask2;
          sz=__builtin_popcount(mask1)*2;
          ok=1;
          break;
        }
        mp[sum1]=mask;
        mask=getnext(mask);
      } 
    }
  }
  else{
    int k=26;
    int mask=(1<<(k/2))-1; 
    int lmask=((1<<k)-1)^mask;
    while(mask!=lmask){
      int sum1=0, sum2=0;
      for(int i=1;i<=k;++i){
        if(mask&(1<<(i-1))) sum1+=v[i];
        else sum2+=v[i];   
      }
      if(sum1==sum2){
        sz=k;
        solmask=mask;
        ok=1;
        for(int i=1;i<=sz;++i){
          if(solmask&(1<<(i-1))) a.push_back(v[i]);
          else b.push_back(v[i]);
        }
        break;
      }
      mask=getnext(mask);
    }
  }
  if(ok==0){
    cout<<"NO\n";
    return 0;
  }
  vector<int> ans;
  ans.push_back(0);
  for(int i=1;i<=sz;++i){
    int x=ans.back();
    if(i&1) ans.push_back(a[(i-1)/2]);
    else ans.push_back(b[(i-1)/2]);
  }
  int last=0;
  for(int i=0;i<ans.size()-1;++i){
    ans[i]=ans[i]-last;
    last=ans[i];
  }
  ans.pop_back();
  cout<<"YES\n";
  for(auto it:ans) cout<<it<<" ";
  if(n<26){
    for(int i=1;i<=n;++i){
      if(solmask&(1<<(i-1))) continue;
      cout<<v[i]<<" ";
    } 
    cout<<"\n";
  }
  else{
    for(int i=sz+1;i<=n;++i){
      cout<<v[i]<<" ";
    }
  }
  cout<<"\n";
}
