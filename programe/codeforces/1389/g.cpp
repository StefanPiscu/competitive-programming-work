#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, m, k;
vector<vector<pair<int, int>>> out;
vector<vector<int>> outNotBridges;
vector<vector<pair<int, int>>> outComp;
vector<int> comp;
vector<bool> isSpecial;
vector<bool> isSpecialComp;
vector<int> cost;
vector<int> wComp;
vector<int> used;
vector<int> low;
vector<int> tin;




void init(int n){
	out.resize(n+1);
	outNotBridges.resize(n+1);
	used.resize(n+1);
	tin.resize(n+1);
	low.resize(n+1);
	comp.resize(n+1);
	isSpecial.resize(n+1);
	cost.resize(n+1);
}


struct edge{
	int a, b, cost;
};
vector<edge> edges;

int nr;
int timer=0;

void dfs(int x, int fat=0){
	used[x]=1;
	tin[x]=++timer;
	low[x]=tin[x];
	for(auto aux:out[x]){
		auto it=aux.first;
		if(it==fat) continue;
		int cost=aux.second;
		if(used[it]) low[x]=min(low[x], tin[it]);
		else{
			dfs(it, x);
			low[x]=min(low[x], low[it]);
			if(low[it]<=tin[x]){
				outNotBridges[it].push_back(x);
				outNotBridges[x].push_back(it);
			}
			else{
				edges.push_back({x, it, cost});
			}
		}
	}
}

void dfs2(int x, int fat=0){
	comp[x]=nr;
	wComp[nr]+=cost[x];
	isSpecialComp[nr]=isSpecialComp[nr]&&isSpecial[x];

	for(auto it:outNotBridges[x]){
		if(it==fat) continue;
		dfs2(it, x);
	}
}

void getComp(){
	dfs(1);
	isSpecialComp.push_back(0);
	wComp.push_back(0);
	for(int i=1;i<=n;++i){
		if(comp[i]==0){
			nr++;
			isSpecialComp.push_back(0);
			wComp.push_back(0);
			dfs2(i);
		}
	}
}

struct compSolver{
	int n;
	vector<vector<pair<int, int>>> out;
	vector<int> w;
	int totSp=0;
	vector<bool> special;

	vector<int> dp, nrs;
	vector<int> sol;

	compSolver(vector<vector<pair<int, int>>> &_out, vector<int> &_w, vector<bool> &_special){
		out=_out;
		w=_w;
		special=_special;
		n=out.size()-1;
		sol.resize(n+1);
		dp.resize(n+1, 0);
		nrs.resize(n+1, 0);
	}

	int cost(int x, int w){
		if(nrs[x]==totSp||nrs[x]==0) return dp[x];
		else return max(0ll, dp[x]-w);
	}

	void dfs1(int x, int fat){
		nrs[x]=special[x];
		dp[x]=w[x];
		for(auto it:out[x]){
			if(it.first==fat) continue;
			dfs1(it.first, x);
			dp[x]+=cost(it.first, it.second);
			nrs[x]+=nrs[it.first];
		}
	}

	void topdown(int x, int y, int w){
		dp[x]-=cost(y, w);
		nrs[x]-=nrs[y];
		dp[y]+=cost(x, w);
		nrs[y]+=nrs[x];
	}

	void dfs2(int x, int fat){
		sol[x]=dp[x];
		for(auto it:out[x]){
			if(it.first==fat) continue;
			topdown(x, it.first, it.second); 
			dfs2(it.first, x);
			topdown(it.first, x, it.second);
		}
	}

	vector<int> solve(){
		for(int i=1;i<=n;++i){
			totSp+=special[i];	
		}

		//cout<<totSp<<"\n";
		dfs1(1, 0);
		dfs2(1, 0);
		return sol;
	}

};

int32_t main(){
	cin>>n>>m>>k;;
	init(n);
	for(int i=1;i<=k;++i){
		int x;
		cin>>x;
		isSpecial[x]=1;
	}
	for(int i=1;i<=n;++i){
		cin>>cost[i];			
	}
	vector<int> edgeCosts(m+1);
	for(int i=1;i<=m;++i){
		cin>>edgeCosts[i];
	}
	for(int i=1;i<=m;++i){
		int a, b, c;
		cin>>a>>b;
		c=edgeCosts[i];
		out[a].push_back({b, c});
		out[b].push_back({a, c});
	}
	getComp();
	outComp.resize(nr+1);
	for(auto it:edges){
		int a=comp[it.a], b=comp[it.b], c=it.cost;
		//cout<<a<<" "<<b<<" "<<c<<"*\n";
		outComp[a].push_back({b, c});
		outComp[b].push_back({a, c});
	}

	compSolver solver(outComp, wComp, isSpecial);
	vector<int> solComp  = solver.solve();
	for(int i=1;i<=n;++i){
		cout<<solComp[comp[i]]<<" ";
	}
	cout<<"\n";
	return 0;
}
