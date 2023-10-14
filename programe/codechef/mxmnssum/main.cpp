#include <bits/stdc++.h>
using namespace std;

struct aint{
  int n;
  vector<int> val;
  aint(int _n): n(_n+1){
    val.resize(4*n);
  }

  void update(int x, int poz, int l, int r, int cr){
    if(l==r) val[cr]=max(x, val[cr]);
    
  }
  
};

int main(){
 
}