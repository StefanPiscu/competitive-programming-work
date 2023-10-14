#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("fmcm.in");
ofstream fout("fmcm.out");

struct FlowNetwork{

	int n;
	
	struct edge{
		int from, to;
		int cap, flow;
		int cost;
		
	};
	vector<edge> edges;

	vector<vector<int>> out;
	vector<int> ledge;
	vector<int> flow;
	vector<int> price;
	vector<bool> inq;

	FlowNetwork(int n, int s, int t): n(n), s(s), t(t){
		out.resize(n+1);
		ledge.resize(n+1);
		flow.resize(n+1);
		price.resize(n+1);
		inq.resize(n+1);
	}

	void addEdge(int from, int to, int cap, int cost){
		edges.push_back({from, to, cap, 0, cost});
		out[from].push_back(edges.size()-1);
		edges.push_back({to, from, 0, 0, -cost});
		out[to].push_back(edges.size()-1);
	}

	int s, t;

	int pushFlow(){
		queue<int> q;
		fill(ledge.begin(), ledge.end(), -1);
		fill(flow.begin(), flow.end(), 0);
		fill(price.begin(), price.end(), 1e9);
		fill(inq.begin(), inq.end(), 0);
		flow[s]=1e9;	
		ledge[s]=-2;
		price[s]=0;
		q.push(s);
		while(!q.empty()){
			int x=q.front();
			q.pop();
			inq[x]=0;
			for(auto it:out[x]){
				auto e=edges[it];
				if(((price[x]+e.cost)>=price[e.to])||e.cap==e.flow) continue;
				ledge[e.to]=it;
				price[e.to]=price[x]+e.cost;
				flow[e.to]=min(flow[x], e.cap-e.flow);
				if(!inq[e.to]) q.push(e.to), inq[e.to]=1;
			}
		}
		return flow[t];
	}

	pair<int, int> getflow(){
		for(int i=1;i<=n;++i){
			random_shuffle(out[i].begin(), out[i].end());
		}
		int flow=0, cost=0;
		while(int newFlow=pushFlow()){
			flow+=newFlow;
			cost+=price[t]*newFlow;
			int cr=t;
			while(cr!=s){
				edges[ledge[cr]].flow+=newFlow;
				edges[ledge[cr]^1].flow-=newFlow;
				cr=edges[ledge[cr]].from;
			}

		}


		return {flow, cost};
	}

};

int main(){
	int n, m, s, t;
	cin>>n>>m>>s>>t;
	FlowNetwork idk(n, s, t);
	for(int i=1;i<=m;++i){
		int a, b, c, d; 
		cin>>a>>b>>c>>d; 
		idk.addEdge(a, b, c, d);
	}
	auto sol=idk.getflow();
	cout<<sol.second<<"\n";
}