#include <bits/stdc++.h>
using namespace std;

int n, m;
int crval;
vector<int> val;
vector<int> ind;
vector<vector<pair<int, bool>>> out;
vector<int> fat, link;
vector<int> depth;

void init(int n){
	val.resize(n+1);
	ind.resize(n+1);
	out.resize(n+1);
	fat.resize(n+1);
	link.resize(n+1);
	depth.resize(n+1);
}

void compute(int x, int parent=0){
	fat[x]=parent; link[x]=parent;
	for(auto it:out[x]){
		if(it.second==0) continue;
		if(it.first==parent) continue;
		depth[it.first]=depth[x]+1;
		compute(it.first, x);
	}
}

int get(int x){
	if(val[x]==0) return x;
	return link[x]=get(link[x]);
}


int main(){
	cin>>n>>m;
	init(n);
	vector<tuple<int, int, bool>> edges;
	for(int i=1;i<=m;++i){
		int a, b;
		bool c;
		cin>>a>>b>>c;
		out[a].push_back({b, c});
		out[b].push_back({a, c});
		edges.push_back({a, b, c});
	}	
	compute(1);
	int crIndex=0;
	for(auto it:edges){
		int a, b;
		bool c;
		tie(a, b, c)=it;
		if(depth[a]>depth[b]) swap(a, b);
		if(c==1){
			ind[b]=crIndex;
		}
		crIndex++;
	}
	for(auto it:edges){
		int a, b;
		bool c;
		tie(a, b, c)=it;
		if(depth[a]>depth[b]) swap(a, b);
		if(c==1){
			if(val[b]==0){
				val[b]=++crval;
			}
			cout<<val[b]<<" ";
		}
		else{
			vector<pair<int, int>> toSort;
			a=get(a), b=get(b);
			while(a!=b){
				if(depth[a]>depth[b]) swap(a, b);
				val[b]=1e9;
				toSort.push_back({ind[b], b});
				a=get(a), b=get(b);
			}
			sort(toSort.begin(), toSort.end());
			for(auto it:toSort){
				val[it.second]=++crval;
			}
			cout<<++crval<<" ";
		}
	}
	return 0;
}
