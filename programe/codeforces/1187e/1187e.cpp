#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;

struct nod{
	int dp;
	int sz;
	vector<int> out;
};

vector<nod> g;

void compute(int x, int fat){
	g[x].sz=1;
	for(auto it:g[x].out){
		if(it==fat) continue;
		compute(it, x);
		g[x].sz+=g[it].sz;
		g[x].dp+=g[it].dp;
	}
	g[x].dp+=g[x].sz;
}

int ans;
void dfs(int x, int fat, int score){
	ans=max(ans, score);	
	for(auto it:g[x].out){
		if(it==fat) continue;
		dfs(it, x, score+n-2*g[it].sz);
	}
}

int32_t main(){
	cin>>n;
	g.resize(n+1);
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		g[a].out.push_back(b);
		g[b].out.push_back(a);
	}
	compute(1, 0);
	dfs(1, 0, g[1].dp);
	cout<<ans<<"\n";
}
