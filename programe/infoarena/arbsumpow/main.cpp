#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
#define MOD 1000000007
#define int long long

ifstream fin("arbsumpow.in");
ofstream fout("arbsumpow.out");

int n, p;
int v[1000007];
int dp[100007][8];
int comb[8][8];
vector<int> out[100007];

void precalc(int n){
	for(int i=0;i<=n;++i){
		comb[i][0]=comb[i][i]=1;
		for(int j=1;j<i;++j){
			comb[i][j]=comb[i-1][j-1]+comb[i-1][j];
		}
	}
}

int sol;
void dfs(int x){
	for(auto it:out[x]){
		dfs(it);
	}
	int val=1;
	for(int i=0;i<=p;++i){
		dp[x][i]=val;
		val=val*v[x]%MOD;
	}
	for(auto it:out[x]){
		int aux[8];
		for(int i=0;i<=p;++i){
			aux[i]=dp[x][i];
		}
		for(int i=0;i<=p;++i){
			for(int j=0;j<=i;++j){
				aux[i]+=(((dp[x][j]*dp[it][i-j])%MOD)*comb[i][j])%MOD;
				aux[i]%=MOD;
			}
		}
		for(int i=0;i<=p;++i) dp[x][i]=aux[i];
	}
	sol+=dp[x][p];
	sol%=MOD;
}

int32_t main(){
	cin>>n>>p;
	for(int i=1;i<=n;++i) cin>>v[i];
	precalc(p);
	for(int i=2;i<=n;++i){
		int x;
		cin>>x;
		out[x].push_back(i);
	}
	dfs(1);
	cout<<sol<<"\n";
}