#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("ctc.in");
ofstream fout("ctc.out");

int n, m;
vector<vector<int>> in, out;
vector<vector<int>> comps;
vector<int> used;

stack<int> ord;
void dfs1(int x, int fat){
	used[x]=1;
	for(auto it:out[x]){
		if(used[it]) continue;
		dfs1(it, x);
	}
	ord.push(x);
}

vector<int> comp;
void dfs2(int x){
	used[x]=1;
	comp.push_back(x);
	for(auto it:in[x]){
		if(used[it]) continue;
		dfs2(it);
	}
}

int main()
{

	cin>>n>>m;
	out.resize(n+1);
	in.resize(n+1);
	used.resize(n+1);
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		in[b].push_back(a);
	}
	for(int i=1;i<=n;++i) if(!used[i]) dfs1(i, 0);
	fill(used.begin(), used.end(), 0);
	while(!ord.empty()){
		int x=ord.top();
		ord.pop();
		if(used[x]) continue;
		dfs2(x);
		comps.push_back(comp);
		comp.clear();
	}
	cout<<comps.size()<<"\n";
	for(auto c:comps){
		for(auto it:c) cout<<it<<" ";
		cout<<"\n";
	}
	return 0;
}
