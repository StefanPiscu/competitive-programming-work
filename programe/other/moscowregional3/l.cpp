#include <bits/stdc++.h>
using namespace std;
 
#define INF 1LL<<60
 
struct edge{
	int x;
	int res;
	long long cap, flow=0;
	edge(int _x, int _res, long long _cap){
		x=_x, res=_res, cap=_cap;
	}
};
 
vector<edge> e;
 
struct nod{
	int level, ptr;
	vector<int> edges;
};
 
vector<nod> g;
 
int s, t;
 
void add_edge(int a, int b, int c){
	//cout<<a<<" "<<b<<" "<<c<<"*\n";
	g[a].edges.push_back(e.size());
	edge x(b, e.size()+1, c);
	e.push_back(x);
	g[b].edges.push_back(e.size());
	x=edge(a, e.size()-1, 0);
	e.push_back(x);
}
 
bool bfs(){
	for(int i=0;i<g.size();++i){
		g[i].level=0;
		g[i].ptr=0;
	}
	queue<int> q;
	q.push(s);
	g[s].level=1;
	while(!q.empty()){
		int cr=q.front();
		q.pop();
		for(auto it:g[cr].edges){
			edge x=e[it];
			if(g[x.x].level||x.flow==x.cap) continue;
			g[x.x].level=g[cr].level+1;
			q.push(x.x);
		}
	}
	return g[t].level;
}
 
long long dfs(int cr, long long pushed=INF){
	if(pushed==0) return 0;
	if(cr==t) return pushed;
	for(;g[cr].ptr<g[cr].edges.size();++g[cr].ptr){
		int id=g[cr].edges[g[cr].ptr];
		if(g[e[id].x].level!=g[cr].level+1) continue;
		long long sent=dfs(e[id].x, min(pushed, e[id].cap-e[id].flow));
		if(!sent) continue;
		e[id].flow+=sent;
		e[e[id].res].flow-=sent;
		return sent;
	}
	return 0;
}
 
int flow=0;
 
long long getflow(){
	long long sol=0;
	while(bfs()){
		while(long long sent=dfs(s)){
			sol+=sent;
		}
	}
	return sol;
}

int getdist(pair<int, int> a, pair<int, int> b){
	return (a.first-b.first)*(a.first-b.first)+(a.second-b.second)*(a.second-b.second);


}

int n, m, a, b, c, d;
vector<pair<int, int>> stores;
vector<pair<int, int>> orders;

bool check(int x){
	//cout<<"--------\n";
	e.clear();
	g.clear();
	g.resize(2*n+m+3);
	for(int i=1;i<=n;++i){
		add_edge(s, i, c-d);
		add_edge(s, n+i, d);
	}
	for(int i=1;i<=x;++i){
		add_edge(2*n+i, t, 1);
		for(int j=1;j<=n;++j){
			int dist=getdist(orders[i], stores[j]);
			if(dist<=a*a) add_edge(j, 2*n+i, 1);
			if(dist<=b*b) add_edge(n+j, 2*n+i, 1);
		}
	}
	flow=getflow();
	return flow==x;
}

int main(){
	cin>>n>>m>>a>>b>>c>>d;
	g.resize(2*n+m+3);
	s=2*n+m+1, t=2*n+m+2;
	stores.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>stores[i].first>>stores[i].second;
	}
	orders.resize(m+1);
	for(int i=1;i<=m;++i){
		cin>>orders[i].first>>orders[i].second;
	}
	/*
	for(int i=1;i<=n;++i){
		add_edge(s, i, c-d);
		add_edge(s, n+i, d);
	}
	for(int i=1;i<=m;++i){
		add_edge(2*n+i, t, 1);
		for(int j=1;j<=n;++j){
			int dist=getdist(orders[i], stores[j]);
			if(dist<=a*a) add_edge(j, 2*n+i, 1);
			if(dist<=b*b) add_edge(n+j, 2*n+i, 1);
		}
	}
	*/

	
	int st=0, dr=m, sol=0;
	while(st<=dr){
		int mid=(st+dr)/2;
		if(check(mid)) sol=mid, st=mid+1;
		else dr=mid-1;
	}
	if(sol==m) cout<<-1<<"\n";
	else cout<<sol+1<<"\n";
}
