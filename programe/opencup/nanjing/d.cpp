#include <bits/stdc++.h>
using namespace std;

#define int long long

struct FenwickTree{
  int n;
  vector<int> val;

  FenwickTree(int _n): n(_n+1){
    val.resize(n+1);
  }

  void update(int poz, int x){
    for(;poz<=n;poz+=(poz&(-poz))){
      val[poz]+=x;
    }
  }

  int query(int poz){
    int sol=0;
    for(;poz;poz-=(poz&-poz)){
      sol+=val[poz];
    }
    return sol;
  }

};

int const nmax = 100000;
int frec[5 + nmax];

struct solver{
  int n;
  vector<int> v;

  void solve(){
    cin>>n;
    v.resize(n+1);
    for(int i=1;i<=n;++i){
      cin>>v[i];
    }
    FenwickTree aib(n + 1);
    std::cout << 0 << " ";
    int added = 0;
    int result = 0;
    
    std::vector<int> aux;
    aux.push_back(1);
    for(int i = 1;i <= n; i++)
      frec[i] = 0;

    for(int i = 2; i <= n; i++) {
      if(v[i] < v[1]) {
        frec[v[i]]++;
        result += added - aib.query(v[i]);
        if(frec[v[i]] == 1) {
          aib.update(v[i], 1);
          added++;
        }
      } else if(v[1] == v[i]){
        aux.push_back(i);
      } else {
        std::swap(v[1], v[i]);
        result++;

        frec[v[i]] = 1;
        aib.update(v[i], 1);
        added++;
        aux.erase(aux.begin());
        aux.push_back(i);
        for(int j = 0; j < aux.size(); j++) {
          result += (i - aux[j]) - ((int)(aux.size()) - 1 - j);
        }
        aux.clear();
        aux.push_back(1);
      }
      std::cout << result + i - 1 - ((int)aux.size() - 1) << " ";
    }

    cout << "\n";
  }
};

int32_t main(){
  cin.tie(0);
  ios_base::sync_with_stdio(0);
  int t;
  cin>>t;
  while(t--){
    solver x;
    x.solve();
  }
  return 0;
}
