#include <bits/stdc++.h>
using namespace std;

int n, MOD;

struct point{
	int x, y, w;
	vector<int> out;
};
vector<point> v;
vector<long long> cost;
vector<int> used;
vector<unsigned long long> costToAdd;

unsigned long long dist(point a, point b){
	return abs(a.x-b.x)*abs(a.x-b.x)+abs(a.y-b.y)*abs(a.y-b.y);
}

vector<bool> used;
vector<pair<int, int>> costs;
vector<vector<long long>> pows;
int crCost;
int miniCost;

void bkt(int k){
	if(k>=costs.size())
	for(int i=0;i<costs.size();++i){
		if(used[i]) continue;
		used[i]=1;
		int lastCost=crCost;
		crCost=(0LL+crCost+pows[costs[i].second][i+1])%MOD;
		bkt(k+1);
	}
}

void dfs(int x){
	costs.clear();
	pows.clear();
	for(auto it:v[x].out){
		dfs(it);
		costs.push_back({cost[it], 0});
	}
	/*
	cout<<x<<"\n";
	for(auto it:costs) cout<<it<<" ";
	cout<<"\n";
	*/
	sort(costs.begin(), costs.end());
	if(costs.empty()){
		cost[x]=v[x].w%MOD;
		//cout<<x<<" "<<cost[x]<<endl;
		return;
	}
	int nr=0;
	for(int i=0;i<costs.size();++i){
		if(i&&costs[i].first!=costs[i-1].first) nr++;
		costs[i].second=nr;
	}
	nr++;
	used.resize(costs.size());
	pows.resize(nr, vector<long long>(costs.size()+1));
	for(int i=0;i<nr;++i){
		int crPow=1;
		for(int j=1;j<=costs.size();++j){
			crPow=(1LL*crPow*costs[i].first)%MOD;
			pows[i][j]=crPow;
		}
	}
	int minCost=MOD+1;
	do{
		int crCost=v[x].w%MOD;
		int pow=1;
		for(auto it:costs){
			crCost=(0LL+crCost+pows[it.second][pow])%MOD;
			pow++;
		}
		minCost=min(minCost, crCost%MOD);
	}while(next_permutation(costs.begin(), costs.end()));
	cost[x]=minCost;
	//cout<<cost[x]<<"*\n\n";
}

int32_t main(){

	cin>>n>>MOD;
	v.resize(n+1);
	used.resize(n+1, 0);
	costToAdd.resize(n+1, 1e18);
	cost.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>v[i].x>>v[i].y>>v[i].w;
	}
	used[1]=1;
	for(int i=2;i<=n;++i) costToAdd[i]=min(costToAdd[i], dist(v[1], v[i]));
	for(int i=2;i<=n;++i){
		int minPoz=0;
		for(int j=1;j<=n;++j){
			if(used[j]) continue;
			if(costToAdd[j]<costToAdd[minPoz]) minPoz=j;
		}
		int fat=0;
		for(int j=1;j<=n;++j){
			if(used[j]&&costToAdd[minPoz]==dist(v[j], v[minPoz])){
				if(fat==0) fat=j;
				else if(v[fat].out.size()>v[j].out.size()) fat=j;
			}
		}
		cout<<fat<<" "<<minPoz<<"\n";
		v[fat].out.push_back(minPoz);
		used[minPoz]=1;
		for(int i=1;i<=n;++i){
			if(used[i]) continue;
			costToAdd[i]=min(costToAdd[i], dist(v[minPoz], v[i]));
		}
	}
	dfs(1);
	for(int i=1;i<=n;++i) cout<<cost[i]%MOD<<" ";
	cout<<"\n";
	return 0;	
}