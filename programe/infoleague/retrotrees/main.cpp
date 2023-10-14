#include <bits/stdc++.h>
using namespace std;

#define int long long

#define cin fin
#define cout fout

ifstream cin("retrotrees.in");
ofstream cout("retrotrees.out");

int n;
vector<int> fat, sz;

struct edge{
	int u, v, cost;
	bool operator<(const edge &ot)const{
		return cost<ot.cost;
	}
};
int m;
vector<edge> edges;

int getfat(int x){
	if(fat[x]==x) return x;
	return fat[x]=getfat(fat[x]);
}

bool join(int a, int b){
	a=getfat(a), b=getfat(b);
	if(a==b) return 0;
	if(sz[a]<sz[b]) swap(a, b);
	fat[b]=a;
	sz[a]+=sz[b];
	return 1;
}

int32_t main(){
	int n, m;
	cin>>n>>m;
	fat.resize(n+1);
	sz.resize(n+1);
	int nrComp=n;
	for(int i=1;i<=n;++i){
		fat[i]=i, sz[i]=1;
	}
	for(int i=1;i<=m;++i){
		int u, v, cost;
		cin>>u>>v>>cost;
		edges.push_back({u, v, cost});
	}
	sort(edges.begin(), edges.end());
	int cost=0;
	for(auto it:edges){
		if(nrComp<=2) break;
		if(join(it.u, it.v)) cost+=it.cost, nrComp--;
	}
	cout<<cost<<"\n";
}