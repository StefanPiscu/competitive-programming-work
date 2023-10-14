#include <bits/stdc++.h>
using namespace std;

ifstream fin("iepuri2.in");
ofstream fout("iepuri2.out");
#define cin fin
#define cout fout

#define MOD 30011

int n, k;
vector<int> in;
vector<vector<int>> out;
vector<vector<int>> dp;
vector<vector<int>> sp;

void dfs(int x){
	for(int i=k;i;--i){
		dp[x][i]=1;
	}
	for(auto it:out[x]){
		dfs(it);
		for(int i=k;i;--i){
			dp[x][i]=(1LL*dp[x][i]*sp[it][i+1])%MOD;
		}
	}
	for(int i=k;i;--i){
		sp[x][i]=(dp[x][i]+sp[x][i+1])%MOD;
	}
}

int main(){
	cin>>n>>k;
	out.resize(n+1);
	in.resize(n+1);
	dp.resize(n+1, vector<int>(k+2, 0));
	sp.resize(n+1, vector<int>(k+2, 0));
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		in[b]++;
	}
	int root=0;
	for(int i=1;i<=n;++i){
		if(in[i]==0){
			 root=i;
			 break;
		}
	}
	dfs(root);
	cout<<sp[root][1]<<"\n";
	return 0;
}