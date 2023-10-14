#include <bits/stdc++.h>
using namespace std;

int n, m, d;
vector<vector<int>> out;
vector<int> degree;
vector<bool> used(n+1);
vector<int> ans;
vector<int> actualAns;

void dfs(int x){
	used[x]=1;
	ans.push_back(x);
	for(auto it:out[x]){
		if(used[it]) continue;
		dfs(it);
	}
}

int main(){
	cin>>n>>m>>d;
	out.resize(n+1);
	degree.resize(n+1);
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
		degree[a]++;
		degree[b]++;
	}
	queue<int> toPop;
	used.resize(n+1);
	for(int i=1;i<=n;++i){
		if(degree[i]<d) toPop.push(i), used[i]=1;
	}
	while(!toPop.empty()){
		int x=toPop.front();
		toPop.pop();
		for(auto it:out[x]){
			degree[it]--;
			if(used[it]==0&&degree[it]<d) toPop.push(it), used[it]=1;
		}
	}
	for(int i=1;i<=n;++i){
		if(!used[i]){
			ans.clear();
			dfs(i);
			if(ans.size()>actualAns.size()) actualAns=ans;
		}
	}		
	if(actualAns.size()==0) cout<<"NIE\n";
	else{
		cout<<actualAns.size()<<"\n";
		sort(actualAns.begin(), actualAns.end());
		for(auto it:actualAns) cout<<it<<" ";
		cout<<"\n";
	}
	return 0;
}