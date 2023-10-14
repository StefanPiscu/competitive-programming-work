#include <bits/stdc++.h>
using namespace std;

int q, n;
int nr[2000002];
bitset<2000002> b;


int main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  cin>>q;
  for(int i=2;i<=2000001;++i){
    if(b[i]==0){
      for(int j=i;j<=2000001;j+=i){
        b[j]=1;
      }  
      continue;
    }
    for(int j=i;j<=2000001;j+=i){
      nr[j]++;
    }
  }
  while(q--){
    int x;
    cin>>x;
    cout<<nr[x]+1<<"\n";
  }
  return 0;
}