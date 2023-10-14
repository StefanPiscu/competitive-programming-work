#include <bits/stdc++.h>
using namespace std;

int seed=0;

int main(){
  cin>>seed;
  srand(seed);
  cout<<1<<"\n";
  int n=20;
  cout<<n<<"\n";
  for(int i=1;i<=n;++i) cout<<rand()%6+1<<" ";
  cout<<"\n";
  return 0;
}