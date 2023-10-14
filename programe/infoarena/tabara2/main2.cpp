#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("tabara2.in");
ofstream fout("tabara2.out");

int n, s, m;

int aintsz;
vector<int> val;

void update(int poz, int x, int l, int r, int cr){
  if(l==r) val[cr]=max(val[cr], x);
  else{
    int mid=(l+r)/2;
    if(poz<=mid) update(poz, x, l, mid, 2*cr);
    else update(poz, x, mid+1, r, 2*cr+1);
    val[cr]=max(val[2*cr+1], val[2*cr]);
  }
}

int query(int ql, int qr, int l, int r, int cr){
  if(ql==l&&qr==r) return val[cr];
  int mid=(l+r)/2;
  if(qr<=mid) return query(ql, qr, l, mid, 2*cr);
  if(mid<ql) return query(ql, qr, mid+1, r, 2*cr+1);
  return max(query(ql, mid, l, mid, 2*cr), query(mid+1, qr, mid+1, r, 2*cr+1));
}


vector<int> fat, sz, owner, scor;

int get(int x){
  if(fat[x]==x) return x;
  return fat[x]=get(fat[x]);
}

void join(int a, int b){
  a=get(a), b=get(b);
  if(a==b) return;
  if(sz[a]<sz[b]) swap(a, b);
  fat[b]=a;
  sz[a]+=sz[b];
  scor[a]=max(scor[a], scor[b]);
  owner[a]=max(owner[a], owner[b]);
  if(owner[a]) update(owner[a], scor[a], 1, n, 1);
}

int main(){
  cin>>n>>s>>m;
  aintsz=4*n+2;
  val.resize(aintsz, 0);
  fat.resize(s+1);
  sz.resize(s+1);
  owner.resize(s+1);
  scor.resize(s+1);
  for(int i=1;i<=s;++i){
    cin>>scor[i];
    fat[i]=i;
    sz[i]=1;
    owner[i]=0;
  }
  while(m--){
    char t;
    cin>>t;
    if(t=='U'){
      int tip, x, y;
      cin>>tip>>x>>y;
      if(tip==1) join(x, y);
      else{
        y=get(y);
        owner[y]=x;
        update(x, scor[y], 1, n, 1);
      }
    }
    else{
      int l, r;
      cin>>l>>r;
      cout<<query(l, r, 1, n, 1)<<"\n";
    }
  }
}