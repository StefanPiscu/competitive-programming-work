#include <bits/stdc++.h>
using namespace std;

int n=6, m=5;
int seed;
vector<int> par, imp;
map<int, bool> used;

int main(){
  cin>>seed;
  srand(seed);
  cout<<n<<"\n";;
  for(int i=1;i<=n;++i){
    int x=(rand()%10)*2+1;
    if(used.count(x)==0) cout<<x<<" ";
    else i--;
    used[x]=1;
  }
  cout<<"\n";
  return 0;
}