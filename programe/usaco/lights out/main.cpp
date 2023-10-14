#include <bits/stdc++.h>
using namespace std;

#define int long long

ifstream fin("lightsout.in");
ofstream fout("lightsout.out");
#define cin fin
#define cout fout

#define MOD 1000000007
int base=223009;



int n;
vector<int> elem;

int gethash(int i, int j){
  int val=0;
  for(int k=i;k<=j;++k) val=(1LL*val*base%MOD+(elem[k]+100003))%MOD;
  return val;
}

int32_t main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>n; 
  int firstx, firsty;
  cin>>firstx>>firsty;
  int lastx=firstx, lasty=firsty;
  vector<int> sp(n+1);
  elem.resize(n+1, 1);
  for(int i=1;i<n;++i){
    int a, b;
    cin>>a>>b;
    int dx=a-lastx+b-lasty, dir=1;
    if(i%2==0) elem[i]*=-1;
    if(dx<0) dir*=-1, dx*=-1;
    elem[i-1]*=dir;
    elem[i]*=dir;
    elem[i]*=dx;
    sp[i]=sp[i-1]+abs(elem[i]);
    lastx=a, lasty=b;
  }
  int dx=-lastx+firstx-lasty+firsty;
  int dir=1;
  if(n%2==0) elem[n]*=-1;
  if(dx<0) dir*=-1, dx*=-1;
  elem[n-1]*=dir;
  elem[n]*=dir;
  elem[n]*=elem[0];
  elem[n]*=dx;
  sp[n]=sp[n-1]+abs(elem[n]);
  unordered_map<int, int> fr;
  for(int i=1;i<=n;++i){
    for(int j=i;j<n;++j){
      int x=gethash(i, j);
      fr[x]++;
    }
  }
  vector<int> dist(n+1);
  for(int i=1;i<=n;++i){
    int crd=0;
    for(int j=i;j<=n;++j){
      crd+=abs(elem[j]);
      if(j==n){
        dist[i]=crd;
        break;
      }
      int x=gethash(i, j);
      if(fr.find(x)!=fr.end()&&fr[x]==1){
        dist[i]=crd+min(sp[j], sp[n]-sp[j]);
        break;
      }
    }
  }
  int sol=0;
  for(int i=2;i<=n;++i) sol=max(sol, dist[i]-min(sp[i-1], sp[n]-sp[i-1]));
  cout<<sol<<"\n";
}