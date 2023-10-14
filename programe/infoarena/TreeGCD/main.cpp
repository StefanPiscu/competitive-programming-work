#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MOD 1000000007
#define cin fin
#define cout fout
ifstream fin("treegcd.in");
ofstream fout("treegcd.out");

int n, m;
int dp[102][10002];
int nrp[10002];
int mobius[10002];
vector<int> out[102];
int aux[10002];

void getmobius(int m){
		mobius[1]=1;
    for(int i = 2; i <= m; ++i) {
        if(!mobius[i]){
            for(int j = i; j <= m; j += i)
                if(mobius[j] >= 0) ++mobius[j];
            for(int j = i * i; j <= m; j += i * i)
                mobius[j] = -2;
        }
        if(mobius[i] == -2)
            mobius[i] = 0;
        else if(mobius[i]&1)
            mobius[i] = 1;
        else
            mobius[i] = -1;
    }
}

void dfs(int x, int fat){
	bool isLeaf=1;
	for(auto it:out[x]){
		if(it==fat) continue;
		isLeaf=0;
		dfs(it, x);
	}
	for(int i=2;i<=m;++i){
		dp[x][i]=1;
	}
	if(isLeaf){
		return;
	}
	for(auto it:out[x]){
		if(it==fat) continue;
		for(int g=2;g<=m;++g) aux[g]=0;
		for(int g=2;g<=m;++g){
			int nr=0;
			for(int i=g;i<=m;i+=g) nr+=dp[it][i], nr%=MOD;
			for(int i=g;i<=m;i+=g){
				aux[i]+=nr*mobius[g];
				aux[i]+=MOD;
				aux[i]%=MOD;
			}
		}
		for(int g=2;g<=m;++g){
			dp[x][g]=aux[g]*dp[x][g]%MOD;
		}

	}
	/*
	cout<<x<<"\n";
	for(int i=1;i<=m;++i) cout<<aux[i]<<" ";
	cout<<"\n";
	cout<<x<<"\n";
	for(int i=1;i<=m;++i) cout<<dp[x][i]<<" ";
	cout<<"\n";
	*/
}

int32_t main(){
	cin>>n>>m;
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b; 
		out[a].push_back(b);
		out[b].push_back(a);
	}
	getmobius(m);
	dfs(1, 0);
	int sol=0;
	for(int i=2;i<=m;++i) sol+=dp[1][i], sol%=MOD;
	cout<<sol<<"\n";
}