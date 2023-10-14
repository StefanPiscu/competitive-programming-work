#include <bits/stdc++.h>
using namespace std;

int t;

#define mid ((l+r)/2)
struct segmentTree{

  struct Node{
    int nr, sump, sumi;
    Node(int nr=0, int sump=0, int sumi=0):nr(nr), sump(sump), sumi(sumi){}
    Node operator+(const Node &ot) const{
      Node sol;
      sol.nr=nr+ot.nr;
      if(nr%2) sol.sump=sump+ot.sumi, sol.sumi=sumi+ot.sump;
      else sol.sump=sump+ot.sump, sol.sumi=sumi+ot.sumi;
      return sol;
    }
  };


  int n;
  vector<Node> val;

  segmentTree(int _n): n(_n+1){
    val.resize(4*n+4);
  }

  void update(int a, int b, int poz, int l, int r, int cr){
    if(l==r){
      val[cr].nr=(a+b-1)/b;
      val[cr].sump=val[cr].sumi=0;
      int nrimp=(a/b+1)/2, nrpar=(a/b)/2;
      int last=a%b;
      if(val[cr].nr%2){
        val[cr].sumi+=last;
      }
      else val[cr].sump+=last;
      val[cr].sumi+=nrimp*b;
      val[cr].sump+=nrpar*b;
      return;
    }
    if(poz<=mid) update(a, b, poz, l, mid, cr*2);
    else update(a, b, poz, mid+1, r, cr*2+1);
    val[cr]=val[2*cr]+val[2*cr+1];
  }
  void update(int a, int b, int poz){
    //cout<<a<<" "<<b<<" "<<poz<<"\n";
    update(a, b, poz, 1, n, 1);
  }

  int query(){
    return val[1].sumi;
  }

};
#undef mid

struct solver{
  int n;
  vector<int> v;

  void solve(){
    cin>>n;
    v.resize(n+1);
    int maxi=0;
    for(int i=1;i<=n;++i){
      cin>>v[i];
      maxi=max(maxi, v[i]);
    }
    segmentTree aint(n+1); 
    queue<int> elem;
    for(int i=1;i<=n;++i) elem.push(i);
    elem.push(0);
    int b=1;
    while(b<=maxi){
      int x=elem.front();
      elem.pop();
      if(x==0){
        cout<<aint.query()<<"\n";
        b++;
        elem.push(0);
      }
      else{
        if(b>v[x]) continue;
        else{
          aint.update(v[x], b, x); 
          elem.push(x);
        }
      }
    }
  }

};


int main(){
  int t;
  cin>>t;
  while(t--){
    solver x;
    x.solve();
  }
}