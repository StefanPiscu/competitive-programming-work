#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define int long long

struct nod{
  int val, lazy;
};

#define mid ((l+r)/2)
struct segmentTree{
  int n;
  vector<nod> a;
  segmentTree(int n): n(n){
    a.resize(4*n+4);
  }
  void push(int cr, int l, int r){
    if(l!=r){
      a[cr*2].val+=a[cr].lazy, a[cr*2].lazy+=a[cr].lazy;
      a[cr*2+1].val+=a[cr].lazy, a[cr*2+1].lazy+=a[cr].lazy;
    }
    a[cr].lazy=0;
  }
  void update(int ul, int ur, int x, int cr, int l, int r){
    if(ul==l&&ur==r){
      a[cr].lazy+=x;
      a[cr].val+=x;
      return;
    }
    push(cr, l, r);
    if(ul<=mid) update(ul, min(mid, ur), x, 2*cr, l, mid);
    if(mid<ur) update(max(ul, mid+1), ur, x, 2*cr+1, mid+1, r);
    a[cr].val=min(a[2*cr].val, a[2*cr+1].val);
  }
  void update(int ul, int ur, int x){
    update(ul, ur, x, 1, 1, n);
  }
};
#undef mid

struct upds{
  int val;
  int poz;
  int type;
  bool operator<(const upds &ot) const{
    return val<ot.val||(val==ot.val&&type<ot.type); 
  }
};

struct FenwickTree{
  int n;
  vector<int> aib;
  FenwickTree(int _n): n(_n+1){
    aib.resize(n+1);
  }
  void upd(int poz, int x){
    for(;poz<=n;poz+=(poz&-poz)) aib[poz]+=x;
  }
  int qry(int poz){
    int sol=0;
    for(;poz;poz-=(poz&-poz)) sol+=aib[poz];
    return sol;
  }
};

int countInversions(vector<int> a){
  vector<pair<int, int>> ev;
  for(int i=1;i<a.size();++i) ev.push_back({a[i], i});
  FenwickTree aib(a.size());
  sort(ev.rbegin(), ev.rend());
  int sol=0;
  for(auto it:ev){
    sol+=aib.qry(it.second);
    aib.upd(it.second, 1);
  }
  return sol;
}

int32_t main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    int n, m;
    cin>>n>>m;
    vector<int> a(n+1), b(m+1);
    vector<upds> v;
    segmentTree aint(n+1);
    for(int i=1;i<=n+1;++i) aint.update(i, i, i-1);
    for(int i=1;i<=n;++i){
      cin>>a[i], v.push_back({a[i], i, -1}), v.push_back({a[i], i, 1});
    }
    for(int i=1;i<=m;++i) cin>>b[i], v.push_back({b[i], i, 0});
    sort(v.begin(), v.end());
    int sol=0;
    for(auto it:v){
      if(it.type==-1) aint.update(it.poz+1, n+1, -1);
      else if(it.type==1) aint.update(1, it.poz, 1);
      else{
        sol+=aint.a[1].val;
      }
    }
    cout<<sol+countInversions(a)<<"\n";
  }
  return 0;
}
