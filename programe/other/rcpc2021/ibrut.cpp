#include <bits/stdc++.h>
using namespace std;

int n;

bool isPal(string s){
  for(int i=1;i<s.size();++i){
    if(s[i]!=s[s.size()-i]) return 0;
  }
  return 1;
}

int main(){
  int n;
  cin>>n;
  string s;
  cin>>s;
}