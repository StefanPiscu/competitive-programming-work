#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("maxflow.in");
ofstream fout("maxflow.out");


struct edge{
	int from, to, flow, cap;
};

struct Dinic{
	vector<edge> edges;
	vector<vector<int>> net;
	vector<int> level;
	vector<int> ptr;
	int s, t;

	Dinic(int _n, int _s, int _t){
		s=_s, t=_t;
		net.resize(_n+1);
		level.resize(_n+1);
		ptr.resize(_n+1);
	}

	bool bfs(){
		fill(level.begin(), level.end(), 0);
		fill(ptr.begin(), ptr.end(), 0);
		queue<int> q;
		q.push(s);
		level[s]=1;
		while(!q.empty()){
			int x=q.front();
			q.pop();
			for(auto it:net[x]){
				int nx=edges[it].to, flow=edges[it].flow, cap=edges[it].cap;
				if(flow==cap||level[nx]!=0) continue;
				level[nx]=level[x]+1;
				q.push(nx);
			}
		}
		return level[t];
	}

	int dfs(int x, int pushed=1e9){
		if(pushed==0) return 0;
		if(x==t) return pushed;
		for(auto &cr=ptr[x];cr<net[x].size();++cr){
			int it=net[x][cr];
			if(edges[it].flow==edges[it].cap||(level[x]+1)!=level[edges[it].to]) continue;
			int sent=dfs(edges[it].to, min(pushed, edges[it].cap-edges[it].flow));
			if(sent==0) continue;
			edges[it].flow+=sent;
			edges[it^1].flow-=sent;
			return sent;
		}
		return 0;
	}

	int getFlow(){
		int flow=0;
		while(bfs()){
			int sent=0;
			while(sent=dfs(s)) flow+=sent;
			/*
			for(auto it:edges){
				cout<<it.from<<" "<<it.to<<" "<<it.flow<<" "<<it.cap<<"\n";
			}
			cout<<"--------------------------------------\n";
			*/
		}
		return flow;
	}

	void addEdge(int u, int v, int cap){
		net[u].push_back(edges.size());
		edges.push_back({u, v, 0, cap});
		net[v].push_back(edges.size());
		edges.push_back({v, u, 0, 0});
	}

};

int main()
{
	int n, m;
	cin>>n>>m;
	Dinic network(n, 1, n);
	for(int i=1;i<=m;++i){
		int a, b, c;
		cin>>a>>b>>c;
		network.addEdge(a, b, c);
	}
	cout<<network.getFlow()<<"\n";
	return 0;
}
