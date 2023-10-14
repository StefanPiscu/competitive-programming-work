#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("tabara2.in");
ofstream fout("tabara2.out");

#define mid ((l+r)/2)
struct segmentTree{

  segmentTree(int _n): n(_n){
    val.resize(4*n+2, 0);
  }

  int n;
  vector<int> val;

  void update(int poz, int x, int l, int r, int cr){
    if(l==r) val[cr]=max(x, val[cr]);
    else{
      if(poz<=mid) update(poz, x, l, mid, 2*cr);
      else update(poz, x, mid+1, r, 2*cr+1);
      val[cr]=max(val[2*cr], val[2*cr+1]);
    }
  }
  void update(int poz, int x){
    update(poz, x, 1, n, 1);
  }
  int query(int ql, int qr, int l, int r, int cr){
    if(ql==l&&qr==r) return val[cr];
    if(qr<=mid) return query(ql, qr, l, mid, 2*cr);
    if(mid<ql) return query(ql, qr, mid+1, r, 2*cr+1);
    return max(query(ql, mid, l, mid, 2*cr), query(mid+1, qr, mid+1, r, 2*cr+1));
  }
  int query(int ql, int qr){
    return query(ql, qr, 1, n, 1);
  }


};
#undef mid


int n, s, m;
vector<int> fat;
vector<int> sz, nrs;
vector<int> owner;

int get(int x){
  if(x==fat[x]) return x;
  return fat[x]=get(fat[x]);
}

void join(int a,  int b, segmentTree &aint){
  a=get(a), b=get(b);
  if(a==b) return;
  if(sz[a]<sz[b]) swap(a, b);
  fat[b]=a;
  sz[a]+=sz[b];
  nrs[a]=max(nrs[a], nrs[b]);
  owner[a]=max(owner[a], owner[b]);
  if(owner[a]!=-1) aint.update(owner[a], nrs[a]);
}

int main(){
  cin>>n>>s>>m;
  fat.resize(s+1);
  sz.resize(s+1);
  nrs.resize(s+1);
  owner.resize(s+1);
  for(int i=1;i<=s;++i){
    cin>>nrs[i];
    fat[i]=i;
    sz[i]=1;
    owner[s]=-1;
  }
  segmentTree aint(n+1);
  while(m--){
    char t;
    cin>>t;
    if(t=='U'){
      int tip;
      cin>>tip;
      if(tip==1){
        int a, b;
        cin>>a>>b;
        join(a, b, aint);
      }
      else{
        int a, b;
        cin>>a>>b;
        b=get(b);
        owner[b]=a;
        aint.update(a, nrs[b]);
      }
    }
    else{
      int l, r;
      cin>>l>>r;
      cout<<aint.query(l, r)<<"\n";
    }
  }
  return 0;
}