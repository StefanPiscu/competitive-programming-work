#include <bits/stdc++.h>
using namespace std;


vector<int> fat, nrSons, crTier;
vector<vector<int>> out;
vector<vector<int>> contor;
vector<pair<int, int>> nodes;

void dfs(int x, int par){
	fat[x]=par;
	for(auto it:out[x]){
		if(it==par) continue;
		dfs(it, x);
		nrSons[x]++;
	}
}

int sol;
void activate(int x, int tier, int k, int nr){
	if(tier<=crTier[x]) return;
	assert((tier-crTier[x])<=1);
	sol+=nr*(tier-crTier[x]);
	crTier[x]=tier;
	if(x==1) return;
	contor[fat[x]][tier]++;
	if(contor[fat[x]][tier]>=k) activate(fat[x], tier+1, k, nr);
	else activate
}

int main(){
	int n;
	cin>>n;
	fat.resize(n+1);
	contor.resize(n+1, vector<int>(6));
	out.resize(n+1);
	nrSons.resize(n+1, 0);
	crTier.resize(n+1, 1);
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	dfs(1, 0);
	for(int i=1;i<=n;++i){
		nodes.push_back({nrSons[i], i});
	}
	sort(nodes.rbegin(), nodes.rend());
	int bnd=1;
	sol=n*(n-bnd+1);
	while(bnd*bnd*bnd*bnd*bnd<=n) bnd++;
	int cr=0;
	for(int k=n;k>=bnd;--k){
		while(cr<nodes.size()&&nodes[cr].first==k){
			activate(nodes[cr].second, 2, k, k-bnd+1);
			cr++;
		}
	}
	for(int k=1;k<bnd;++k){
		//solve for k=i
	}

}