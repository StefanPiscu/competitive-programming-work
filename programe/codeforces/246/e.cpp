#include <bits/stdc++.h>
using namespace std;


vector<string> name;
vector<vector<int>> out;
vector<int> depth;
vector<int> sz;
vector<vector<pair<int, int>>> qrys;
vector<int> sol;


void init(int n){
	name.resize(n+1);
	out.resize(n+1);	
	depth.resize(n+1);
	sz.resize(n+1);
	qrys.resize(n+1);
}

void preDfs(int x){
	sz[x]=1;
	for(auto iter=out[x].begin();iter!=out[x].end();++iter){
		auto &it = *iter;
		depth[it]=depth[x]+1;
		preDfs(it);
		sz[x]+=sz[it];
		if(sz[it]>sz[out[x][0]]) swap(it, out[x][0]);
	}
}


void dfs(int x, deque<unordered_set<string>> &v){
	if(out[x].size()>0) dfs(out[x][0], v);
	v.push_front({});
	v[0].insert(name[x]);
	if(out[x].size()>0){
		for(auto iter=out[x].begin()+1;iter!=out[x].end();++iter){
			auto &it = *iter;
			deque<unordered_set<string>> tempV;
			dfs(it, tempV);
			for(int i=0;i<tempV.size();++i){
				if(v.size()<=(i+1)) v.push_back({});
				for(auto it:tempV[i]){
					v[i+1].insert(it);
				}
			}
		}
	}

#ifdef DEBUG
	cout<<x<<"\n";
	for(int i=0;i<v.size();++i){
		cout<<"  "<<i<<": ";
		for(auto it:v[i]) cout<<it<<" ";
		cout<<"\n";
	}
	cout<<"\n";
#endif

	for(auto it:qrys[x]){
		int k, ind;
		tie(k, ind)=it;
		if(k>=v.size()) sol[ind]=0;
		else sol[ind]=v[k].size();
	}
}

void dfs(int root){
	deque<unordered_set<string>> v;
	dfs(root, v);
}

int main(){
	int n;
	cin>>n;
	init(n);
	vector<int> roots;
	for(int i=1;i<=n;++i){
		cin>>name[i];
		int fat;
		cin>>fat;
		if(fat) out[fat].push_back(i);
		else roots.push_back(i);
	}
	int m;
	cin>>m;
	sol.resize(m+1);
	for(int i=1;i<=m;++i){
		int v, k;
		cin>>v>>k;
		qrys[v].push_back({k, i});
	}
	for(auto root:roots){
		preDfs(root);
		dfs(root);
	}
	for(int i=1;i<=m;++i) cout<<sol[i]<<"\n";
	return 0;
}