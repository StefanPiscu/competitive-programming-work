#include <bits/stdc++.h>
using namespace std;

#define int long long

struct Dinic{
	struct edge{
		int u, v;
		int cap, flow;
	};	
	vector<edge> edges;
	vector<int> level;
	vector<vector<int>> out;
	vector<int> p;

	int n;
	int s, t;
	Dinic(int _n, int _s, int _t){
		n=_n;	
		s=_s, t=_t;
		level.resize(n+1);
		p.resize(n+1);
		out.resize(n+1);
	}

	void add_edge(int u, int v, int cap){
		out[u].push_back(edges.size());
		edges.push_back({u, v, cap, 0});
		out[v].push_back(edges.size());
		edges.push_back({v, u, 0, 0});
	}

	bool bfs(){
		queue<int> q;
		q.push(s);
		fill(level.begin(), level.end(), 0);
		fill(p.begin(), p.end(), 0);
		level[s]=1;
		while(!q.empty()){
			int x=q.front();
			q.pop();
			for(auto it:out[x]){
				if(edges[it].flow==edges[it].cap) continue;
				int to=edges[it].v;
				if(level[to]==0) level[to]=level[x]+1, q.push(to);
			}
		}
		return level[t];
	}

	int dfs(int x, int pushed=1e9){
		if(pushed==0) return 0;
		if(x==t) return pushed;
		for(;p[x]<out[x].size();++p[x]){
			int e=out[x][p[x]];
			int to=edges[e].v;
			int cap=edges[e].cap;
			int flow=edges[e].flow;
			if((level[x]+1)!=level[to]) continue;
			int sent=dfs(to, min(pushed, cap-flow));
			if(sent){
				edges[e].flow+=sent;
				edges[e^1].flow-=sent;
				return sent;
			}
		}
		return 0;
	}

	int getflow(){
		int flow=0;
		while(bfs()){
			while(int sent=dfs(s)){
				flow+=sent;
			}
		}
		return flow;
	}

};

int32_t main(){
	int n, m;
	cin>>n>>m;
	Dinic network=Dinic(n, 1, n);	
	for(int i=1;i<=m;++i){
		int a, b, c;
		cin>>a>>b>>c;
		network.add_edge(a, b, c);
	}
	cout<<network.getflow()<<"\n";
	return 0;
}