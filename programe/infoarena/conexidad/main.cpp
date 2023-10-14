#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream cin("conexidad.in");
ofstream cout("conexidad.out");


int n, m;
vector<bool> used;
vector<vector<int>> out;
vector<int> rep;
vector<vector<int>> excess;
vector<int> izolated, freeNodes;

void dfs(int x){
	if(rep.back()==0) rep.back()=x;
	else excess.back().push_back(x);
	used[x]=1;
	for(auto it:out[x]){
		if(used[it]) continue;
		dfs(it);
	}
}


int main(){
	cin>>n>>m;
	if(n==1){
		cout<<0<<"\n";
		return 0;
	}
	out.resize(n+1);
	used.resize(n+1);
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	for(int i=1;i<=n;++i){
		if(!used[i]){
			rep.push_back(0);
			excess.push_back({});
			dfs(i);
		}
	}
	int last=0;
	vector<pair<int, int>> sol;
	for(int i=0;i<rep.size();++i){
		if(excess[i].size()==0){
			izolated.push_back(rep[i]);
		}
		else{
			if(last==0){
				last=rep[i];
				for(auto it:excess[i]) freeNodes.push_back(it);
			}
			else{
				sol.push_back({last, rep[i]});
				last=excess[i][0];
				for(int j=1;j<excess[i].size();++j) freeNodes.push_back(excess[i][j]);
			}
		}
	}
	
	/*
	for(auto it:izolated) cout<<it<<" ";
	cout<<"\n";
	for(auto it:freeNodes) cout<<it<<" ";
	cout<<"\n";
	cout.flush();
	*/
	
	if(last!=0) freeNodes.push_back(last);
	int nrMax=0;
	if(izolated.size()==1&&freeNodes.size()==0){
		nrMax=0;
	}
	else if(izolated.size()==2&&freeNodes.size()==0){
		nrMax=1;
		sol.push_back({izolated[0], izolated[1]});
	}
	else if(izolated.size()>freeNodes.size()){
		nrMax=2;
		for(int i=1;i<izolated.size();++i){
			sol.push_back({izolated[i-1], izolated[i]});
		}
		if(freeNodes.size()) sol.push_back({izolated[0], freeNodes[0]});
	}
	else{
		nrMax=1;
		for(int i=0;i<izolated.size();++i){
			sol.push_back({freeNodes[i], izolated[i]});
		}
	}
	cout<<nrMax<<"\n";
	cout<<sol.size()<<"\n";
	for(auto it:sol) cout<<it.first<<" "<<it.second<<"\n";
}