#include <bits/stdc++.h>
using namespace std;

#define int long long

#define cin fin
#define cout fout

ifstream fin("aquapark.in");
ofstream fout("aquapark.out");

int n, m, c;
vector<int> fat, sz;
vector<vector<int>> sons;
vector<tuple<int, int, int>> edges;

void show(int i, int color=1){
	int a, b, ind;
	tie(a, b, ind)=edges[i];
	cout<<a<<" "<<b<<" "<<color<<"\n";
	for(auto it:sons[i]){
		show(it, 3-color);
	}
}


int get(int x){
	if(fat[x]==x) return x;
	return get(fat[x]);
}

int nr;

void join(int a, int b){
	a=get(a), b=get(b);
	if(a==b) return;
	nr--;
	if(sz[a]<sz[b]) swap(a, b);
	fat[b]=a;
	sz[a]+=sz[b];
	sons[a].push_back(b);
}



int32_t main(){
	cin>>c>>n>>m;

	edges.push_back({0, 0, 0});
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		if(a>b) swap(a, b);
		edges.push_back({a, b, i});
	}
	fat.resize(m+1);
	sz.resize(m+1);
	sons.resize(m+1);
	for(int i=1;i<=m;++i) fat[i]=i, sz[i]=1;
	vector<pair<int, int>> events;
	for(auto it:edges){
		int a, b, ind;
		tie(a, b, ind)=it;
		events.push_back({a, ind});
		events.push_back({b, -ind});
	}
	sort(events.begin(), events.end());
	stack<int> active;
	vector<bool> used(m+1);
	nr=m;
	for(auto it:events){
		int x=it.second;
		int a, b, ind;
		tie(a, b, ind) = edges[abs(x)];
		if(x<0){
			used[ind]=1;
			int last=0;
			while(!active.empty()){
				int a2, b2, ind2;
				tie(a2, b2, ind2)=edges[active.top()];
				if(used[ind2]){
					active.pop();
					continue;
				}
				if(a2>a){
					join(ind, ind2);
					last=ind2;
					active.pop();
				}
				else{
					break;
				}
			}
			if(last) active.push(last);
			if(active.empty()) continue;
		}
		else{
			while(!active.empty()){
				int a2, b2, ind2;
				tie(a2, b2, ind2)=edges[active.top()];
				if(used[ind2]){
					active.pop();
					continue;
				}
				if(b2<b) active.pop();
				else break;
			}
			active.push(x);
		}
	}
	if(c==2){
		int sol=1;
		while(nr--){
			sol=sol*2%666013;
		}
		cout<<sol<<"\n";
	}
	else{
		for(int i=1;i<=n;++i){
			if(fat[i]==i) show(i);
		}
	}
	return 0;
}