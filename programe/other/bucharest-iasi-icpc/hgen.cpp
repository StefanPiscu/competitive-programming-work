#include <bits/stdc++.h>
using namespace std;

int seed;
int n=1000, m=100;

int main(){
  cin>>seed;
  srand(seed);
  cout<<n<<" "<<m<<"\n";
  for(int i=1;i<=m;++i){
    int rv=rand()%8;
    cout<<rand()%(n+1)<<" "<<rand()%(n+1)<<" "<<rv*rv*rv<<"\n";
  }
}