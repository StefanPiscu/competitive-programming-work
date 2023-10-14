#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007
#define cin fin
#define cout fout
ifstream cin("tairos.in");
ofstream cout("tairos.out");


int n, d;
vector<vector<int>> out;
vector<int> dist;
vector<int> dp;

void calc(int x, int fat){
	for(auto it:out[x]){
		if(it==fat) continue;
		dist[it]=dist[x]+1;
		calc(it, x);
	}
}

void dfs(int d, int x, int fat){
	if(dist[x]==d){
		dp[d]++;
		dp[d]%=MOD;
	}
	bool isLeaf=1;
	for(auto it:out[x]){
		if(it==fat) continue;
		isLeaf=0;
		dfs(d, it, x);
	}
	if(isLeaf){
		if(dist[x]<d){
			dp[d]+=dp[d-dist[x]];
			dp[d]%=MOD;
		}
	}
}


int main(){
	cin>>n>>d;
	out.resize(n+1);
	dist.resize(n+1);
	dp.resize(d+1);
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	calc(1, 0);
	for(int i=1;i<=d;++i) dfs(i, 1, 0);
	cout<<dp[d]%MOD<<"\n";
}