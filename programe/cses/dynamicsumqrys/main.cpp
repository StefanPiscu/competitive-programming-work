#include <bits/stdc++.h>
using namespace std;
 
int n, q;
int aint[4*200001];
 
int join(int a, int b){
  return a+b;
}
 
void update(int x, int poz, int l, int r, int cr){
  if(l==r){ //cazul special care este in frunza
    aint[cr]=x;
    return;
  }
  int mid=(l+r)/2;
  if(poz<=mid) update(x, poz, l, mid, 2*cr);
  else update(x, poz, mid+1, r, 2*cr+1);
  aint[cr]=join(aint[2*cr],aint[2*cr+1]);
}
 
int counter=100;
int query(int ql, int qr, int l, int r, int cr){
	cerr<<ql<<" "<<qr<<" "<<l<<" "<<r<<" "<<cr<<"\n";
	counter--;
	if(counter==0) exit(0);
  if(l==ql&&r==qr) return aint[cr];
  int mid=(l+r)/2;
  //daca queryul e complet in partea stanga
  if(qr<mid) return query(ql, qr, l, mid, 2*cr);
  //daca queryul e complet in partea dreapta
  if(ql>=mid) return query(ql, qr, mid+1, r, 2*cr+1);
  //daca query e si in stanga si in dreapta
  //impartim queryul in 2 de la ql---mid, si mid+1---qr
  return join(query(ql, mid, l, mid, 2*cr),query(mid+1, qr, mid+1, r, 2*cr+1));
}
 
 
int main(){
  cin>>n>>q;
  for(int i=1;i<=n;++i){
    int x;
    cin>>x;
    update(x, i, 1, n, 1);
  }
  while(q--){
    int t;
    cin>>t;
		cout<<q<<"\n";
    if(t==2){
      int l, r;
      cin>>l>>r;
      cout<<query(l, r, 1, n, 1)<<"\n";
    }
    else{
      int poz, x;
      cin>>poz>>x;
      update(x, poz, 1, n, 1);
    }
  }
  return 0;
}