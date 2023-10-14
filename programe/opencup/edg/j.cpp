#include <bits/stdc++.h>
using namespace std;

struct SuffixArray{
  struct suffix{
    int ind;
    int rank[2];

    bool operator<(const suffix &ot){
      return rank[0]<ot.rank[0]||(rank[0]==ot.rank[0]&&rank[1]<ot.rank[1]);
    }
  };

  int n;
  string s;
  vector<int> ord;
  vector<int> poz;
  
  SuffixArray(string _s): s(_s){
    n=s.size();
    vector<suffix> elem(n);
    ord.resize(n);
    poz.resize(n);
    for(int i=0;i<n;++i) elem[i].ind=i, elem[i].rank[0]=(s[i]-'a'), elem[i].rank[1]=(i+1==n)?(-1):(s[i+1]-'a');
    sort(elem.begin(), elem.end());
    for(int i=0;i<n;++i) poz[elem[i].ind]=i;
    for(int k=2;k<n;k*=2){
      int cnt=0;
      int prevrank=elem[0].rank[0];
      elem[0].rank[0]=cnt;
      for(int i=1;i<n;++i){
        if(elem[i].rank[0]!=prevrank || elem[i].rank[1]!=elem[i-1].rank[1]) cnt++;
        prevrank=elem[i].rank[0];
        elem[i].rank[0]=cnt;
      }
      for(int i=0;i<n;++i){
        elem[i].rank[1]=(elem[i].ind+k<n)?(elem[poz[elem[i].ind+k]].rank[0]):(-1);
      }
      sort(elem.begin(), elem.end());
      for(int i=0;i<n;++i) poz[elem[i].ind]=i;
    }
    for(int i=0;i<n;++i) ord[i]=elem[i].ind;
  }

  vector<int> lcp;
  void kasai(){
    int k=0;
    lcp.resize(n);
    for(int i=0;i<n;++i){
      if(poz[i]==n-1){
        k=0;
        continue;
      }
      int j=ord[poz[i]+1];
      while((i+k)<n&&(j+k)<n&&s[i+k]==s[j+k]) k++;
      lcp[poz[i]]=k;
      if(k) k--;
    }
  }
};

struct FenwickTree{
  int n;
  vector<int> val;

  FenwickTree(int _n): n(_n+1){
    val.resize(n+1);
  }

  void upd(int poz, int x){
    poz++;
    for(;poz<=n;poz+=(poz&-poz)) val[poz]+=x;
  }

  void getK(int k){
    int step=1<<(31-__builtin_clz(n));
    int cr=0, sol=0;
    while(step){
      if(cr+val[sol+step]<=k) sol+=step;
      step>>=1;
    }
    return sol;
  }
}


int main(){
  string s;
  cin>>s;
  SuffixArray sufar(s);
  sufar.kasai();
  int i=0;
  vector<pair<int, int>> spliters;
  for(int i=0;i<sufar.lcp.size();++i){
    spliters.push_back({sufar.lcp[i], i});
  }
  sort(spliters.begin(), spliters.end());
  int nrq=0;
  vector<pair<int, int>> qrys;
  for(int i=1;i<=nrq;++i){
    int x;
    cin>>x;
    qrys.push_back({x, i});
  }
  sort(qrys.begin(), qrys.end()+1);
  vector<int> ans(nrq+1);
  int p=0;
  int l=1;
  FenwickTree aib(s.size()+2);
  while(p<spliters.size()&&spliters[p].first<l){
    aib.upd(spliters[p].second+1, 1);
    p++;
  }
  int nr=0;
  for(auto it:qrys){
    while((nr+(p+1))<x)){
      nr+=(p+1)
    }
  }
  return 0;
}
