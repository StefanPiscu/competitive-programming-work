#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("biconex.in");
ofstream fout("biconex.out");


int n, m;
vector<vector<int>> out;
vector<int> depth, low;
vector<vector<int>> comps;

stack<int> stk;
void dfs(int x, int fat){
	depth[x]=depth[fat]+1;
	low[x]=depth[x];
	stk.push(x);
	for(auto it:out[x]){
		if(it==fat) continue;
		if(depth[it]){
			low[x]=min(low[x], depth[it]);
			continue;
		}
		dfs(it, x);
		if(low[it]>=depth[x]){
			vector<int> comp;
			while(!stk.empty()&&stk.top()!=it){
				comp.push_back(stk.top());
				stk.pop();
			}
			comp.push_back(it);
			comp.push_back(x);
			stk.pop();
			comps.push_back(comp);
		}
		low[x]=min(low[x], low[it]);
	}
}

int main()
{
	cin>>n>>m;
	out.resize(n+1);
	depth.resize(n+1);
	low.resize(n+1);
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	dfs(1, 0);
	cout<<comps.size()<<"\n";
	for(auto comp:comps){
		for(auto it:comp) cout<<it<<" ";
		cout<<"\n";
	}
	return 0;
}
