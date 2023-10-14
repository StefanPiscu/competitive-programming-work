#include <bits/stdc++.h>
using namespace std;

int n, m, x;
vector<vector<pair<int, int>>> out;
vector<int> v;
vector<int> fat;

int get(int x){
	if(fat[x]==x) return x;
	return fat[x]=get(fat[x]);
}

priority_queue<pair<int, int>> pq;

void join(int a, int b){
	a=get(a), b=get(b);
	if(out[a].size()<out[b].size()) swap(a, b);
	fat[b]=a;
	v[a]=v[a]+v[b]-x;
	v[b]=0;
	while(!out[b].empty()){
		auto aux=out[b].back();
		out[b].pop_back();
		int to=get(aux.first);
		if(to==a) continue;
		out[a].push_back({to, aux.second});
	}
	
	while(out[a].size()>0&&get(out[a].back().first)==a) out[a].pop_back();
	pq.push({v[a], a});
}

int main(){
	cin>>n>>m>>x;
	v.resize(n+1);
	out.resize(n+1);
	int sum=0;
	for(int i=1;i<=n;++i) cin>>v[i], sum+=v[i], pq.push({v[i], i});
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back({b, i});
		out[b].push_back({a, i});
	}
	if(sum<(n-1)*x){
		cout<<"NO\n";
		return 0;
	}
	else{
		cout<<"YES\n";
		int nr=n-1;
		fat.resize(n+1);
		for(int i=1;i<=n;++i) fat[i]=i;
		while(nr--){
			auto aux=pq.top();
			pq.pop();
			int x=aux.second;
			if(v[x]==0){
				nr++;
				continue;
			}
			cout<<out[x].back().second<<"\n";
			join(x, out[x].back().first);
		}
	}

}