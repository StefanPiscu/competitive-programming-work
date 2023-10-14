#include <bits/stdc++.h>
using namespace std;

int n;
vector<bool> para;
vector<vector<int>> out;

void dfs(int x, int fat=0, int d=1){
	para[x]=d%2;
	for(auto it:out[x]){
		if(it==fat) continue;
		dfs(it, x, d+1);
	}
}

int main(){
	cin>>n;
	para.resize(n+1);
	out.resize(n+1);
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	dfs(1);
	for(int i=1;i<=n;++i){
		if(para[i]) cout<<"(";
		else cout<<")";
	}
	cout<<"\n";
	return 0;
}