#include <bits/stdc++.h>
using namespace std;
 
 
int n, k;
long long dp[2][100005];
vector<int> a;
vector<int> ma;
vector<int> b;
 
int lg(int x){
  return 63-__builtin_clzll(x);
}
 
struct rmq{
  struct elem{
    vector<int> sz;
  };
  vector<elem> maxi;
  rmq(vector<int> v={}){
    maxi.resize(v.size());
    for(int i=1;i<v.size();++i){
      maxi[i].sz.push_back(v[i]);
    }
    for(int pow=1;2*pow<v.size();pow*=2){
      for(int i=1;i+2*pow-1<v.size();++i){
        int val=max(maxi[i].sz.back(), maxi[i+pow].sz.back());
        maxi[i].sz.push_back(val);
      }
    }
  }
  int get(int a, int b){
    int x=lg(b-a);
    return max(maxi[a].sz[x], maxi[b-(1<<x)+1].sz[x]);
  }
};

rmq armq, marmq;

int cost(int l, int r, int k){
	int x=armq.get(l, r), y=-marmq.get(l, r);
	int valx=1, valy=1;
	while(k--){
		valx*=x;
		valy*=y;
	}
	return valx-valy;
}
 
void computeLayer(int I, int l, int r, int optl, int optr){
	int mid=(l+r)/2;
	int opt=optl;
	int layer=I%2;
	int llayer=1-layer;
	int best=dp[llayer][opt-1]+cost(opt, mid, b[I]);

	for(int i=optl+1;i<=optr&&i<=mid;++i){
		int val=dp[llayer][i-1]+cost(i, mid, b[I]);
		if(val>best){
			opt=i;
			best=val;
		}
	}
	dp[layer][mid]=best;
	if(l<mid) computeLayer(I, l, mid-1, optl, opt);
	if(mid<r) computeLayer(I, mid+1, r, opt, optr); 
}
 
int32_t main(){
	cin>>n>>k;
	a.resize(n+1);
	ma.resize(n+1);
	b.resize(k+1);
	for(int i=1;i<=n;++i){
		cin>>a[i];
		ma[i]=-a[i];
	}
	for(int i=1;i<=k;++i){
		cin>>b[i];
	}
	armq=rmq(a);
	marmq=rmq(ma);
	for(int i=0;i<=n;++i) dp[0][i]=dp[1][i]=0;
	for(int i=1;i<=k;++i){
		computeLayer(i, 1, n, 1, n);
	}
	cout<<dp[k%2][n]<<"\n";
	return 0;
}