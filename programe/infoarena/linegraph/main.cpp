#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("linegraph.in");
ofstream fout("linegraph.out");

int n, m;
bitset<1002> adj[1002][1002];
vector<int> comp[1002];
int c1[1002], c2[1002];
int grad[1002];
int tin[1002], low[1002];
int nr=0;
int nrc=0;

vector<int> out[1002];
bool used[1002];

bool dfs(int x, int fat){
	used[x]=1;
	for(auto it:out[x]){
		if(it==fat) continue;
		if(used[it]) return 0;
		if(!dfs(it, x)) return 0;
	}
	return 1;
}

stack<int> st;

void getbiconexe(int x){
	tin[x]=low[x]=++nr;
	st.push(x);
	for(int j=1;j<=n;++j){
		if(adj[x][j]==0) continue;
		if(tin[j]) low[x]=min(low[x], tin[j]);
		else{
			getbiconexe(j);
			low[x]=min(low[j], low[x]);
			if(low[j]>=tin[x]){
				nrc++;
				comp[nrc].clear();
				while(st.top()!=x){
					comp[nrc].push_back(st.top());
					st.pop();
				}
				comp[nrc].push_back(x);
			}
		}
	}
}

void solve(){
	cin>>n>>m;
	memset(adj, 0, sizeof(adj));
	memset(tin, 0, sizeof(tin));
	memset(low, 0, sizeof(low));
	memset(grad, 0, sizeof(tin));
	memset(c1, 0, sizeof(low));
	memset(c2, 0, sizeof(low));
	nr=0, nrc=0;
	for(int i=1;i<=m;++i){
		int a, b; 
		cin>>a>>b; 
		adj[a][b]=adj[b][a]=1;
	}
	getbiconexe(1);
	for(int i=1;i<=nrc;++i){
		for(auto it:comp[i]){
			
		}
		cout<<"\n";
	}
	cout<<"\n";
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}