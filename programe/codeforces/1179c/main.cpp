#include <bits/stdc++.h>
using namespace std;

#define mid ((l+r)/2)
struct nod{
  int val=0;
  int lazy=0;
  nod *ls=nullptr, *rs=nullptr;

  void push(){
    if(ls==nullptr) ls=new nod;
    if(rs==nullptr) rs=new nod;
    ls->val+=lazy;
    ls->lazy+=lazy;
    rs->val+=lazy;
    rs->lazy+=lazy;
    lazy=0;
  }

  void upd(int x, int pl, int pr, int l=1, int r=1000002){
    if(l==pl&&r==pr){
      val+=x, lazy+=x;
      return;
    }
    //cout<<l<<" "<<r<<" "<<mid<<" "<<pl<<" "<<pr<<" "<<this<<endl;
    push();
    //cout<<l<<" "<<r<<" "<<mid<<" "<<pl<<" "<<pr<<endl;
    if(pl<=mid) ls->upd(x, pl, min(mid, pr), l, mid);
    if(mid<pr) rs->upd(x, max(mid+1, pl), pr, mid+1, r);
    val=min(ls->val, rs->val);
  }

  int get(int l=1, int r=1000002){
    if(l==r) return l;
    push();
    if(rs->val<0) return rs->get(mid+1, r);
    if(ls->val<0) return ls->get(l, mid);
    return -1;
  }

};

int main(){
  int n, m;
  cin>>n>>m;
  vector<int> a(n+1), b(m+1);
  nod *root=new nod;
  for(int i=1;i<=n;++i){
    cin>>a[i];
    root->upd(-1, 1, a[i]);
  }
  for(int i=1;i<=m;++i){
    cin>>b[i];
    root->upd(1, 1, b[i]);
  }
  int q=0;
  cin>>q;
  while(q--){
    int t, i, x;
    cin>>t>>i>>x;
    int sign=0;
    if(t==1){
      root->upd(1, 1, a[i]);
      a[i]=x;
      root->upd(-1, 1, a[i]);
    }
    else{
      root->upd(-1, 1, b[i]);
      b[i]=x;
      root->upd(1, 1, b[i]);
    }
    cout<<root->get()<<"\n";
  }
  return 0;
}