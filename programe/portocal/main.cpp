#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int c;
int k, n, m;
vector<int> s;
vector<vector<int>> out;
vector<int> dp[2], num[2];
vector<int> val;
vector<int> sz, nrc, depth;

int binpow(int b, int e){
	int sol=1;
	while(e){
		if(e&1) sol=1LL*sol*b%MOD;
		b=1LL*b*b%MOD;
		e>>=1;
	}
	return sol;
}

void dfsInit(int x, int fat=0){
	sz[x]=1;
	depth[x]=depth[fat]+1;
	nrc[x]=0;
	for(auto it:out[x]){
		if(it==fat) continue;
		dfsInit(it, x);
		sz[x]+=sz[it];
		nrc[x]+=nrc[it]+(val[it]==-1);
	}
}

void dfs(int x, int fat=0){
	int aux1=1, aux2=1;
	vector<int> sp0(out[x].size());
	vector<int> sp01(out[x].size());
	vector<int> nsp0(out[x].size());
	vector<int> nsp01(out[x].size());
	for(auto it:out[x]){
		if(it==fat) continue;
		dfs(it, x);
		aux1+=dp[0][it];
		aux2=1LL*aux2*num[0][it]%MOD;
	}

	for(int i=0;i<(int)out[x].size();++i){
		int it=out[x][i];
		if(it==fat){
			if(i) sp0[i]=sp0[i-1], sp01[i]=sp01[i-1], nsp0[i]=nsp0[i-1], nsp01[i]=nsp01[i-1];
			continue;
		}
		if(i){
			sp0[i]=dp[0][it]+sp0[i-1], nsp0[i]=(1LL*num[0][it]*nsp0[i-1])%MOD;
			int num01=0;
			if(dp[0][it]<dp[1][it]) num01=num[0][it];
			else if(dp[0][it]>dp[1][it]) num01=num[1][it];
			else num01=num[0][it]+num[1][it];
			sp01[i]=min(dp[0][it], dp[1][it])+sp01[i-1], nsp01[i]=(num01+nsp01[i-1])%MOD;
		}
		else{
			sp0[i]=dp[0][it], nsp0[i]=num[0][it];
			int num01=0;
			if(dp[0][it]<dp[1][it]) num01=num[0][it];
			else if(dp[0][it]>dp[1][it]) num01=num[1][it];
			else num01=(num[0][it]+num[1][it])%MOD;
			sp01[i]=min(dp[0][it], dp[1][it]), nsp01[i]=num01;
		}
	}

	if(val[x]==-1){
		int mini=1e9;
		if(s[depth[x]]==m) mini=min(aux1, sz[x]);
		else mini=0;
		dp[0][x]=mini;
		if(mini==aux1) num[0][x]=(num[0][x]+aux1)%MOD;
		if(mini==sz[x]) num[0][x]=(num[0][x]+1LL*(s[depth[x]]-1)*binpow(m, nrc[x])%MOD)%MOD;
		if(mini==0) num[0][x]=(num[0][x]+1LL*(m-s[depth[x]])*binpow(m, nrc[x])%MOD)%MOD;
	}
	else{
		if(val[x]==s[depth[x]]){
			dp[0][x]=aux1;
			num[0][x]=aux2;
		}
		else if(val[x]<s[depth[x]]){
			dp[0][x]=sz[x];
			num[0][x]=binpow(m, nrc[x]);
		}
		if(val[x]==-1||val[x]>s[depth[x]]){
			dp[0][x]=0;
			num[0][x]=binpow(m, nrc[x]);
		}
	}

	int nrg=out[x].size();
	int mini=1e9;
	for(int i=0;i<nrg;++i){
		int it=out[x][i];
		if(it==fat) continue;
		if(i) mini=min(mini, sp0[i-1]+dp[1]it]+sp01[nrg-1]-sp01[i]);
		else mini=min(mini, sp01[nrg-1]-sp01[i]+dp[1][it]);
	}
	dp[1][x]=mini;
	for(int i=0;i<nrg;++i){
		int it=out[x][i];
		if(it==fat) continue;
		if(i){
			if(mini==(sp0[i-1]+dp[1][it]+sp0[nrg-1]-sp[i])) nsp0[i-1]+num[1][it]
		}
	}
}

int main()
{
	cin>>c;
	cin>>k>>n>>m;
	val.resize(n+1);
	sz.resize(n+1);
	nrc.resize(n+1);
	out.resize(n+1);
	for(int i=1;i<=n;++i) cin>>val[i];
	s.resize(k+1);
	for(int i=1;i<=k;++i){
		cin>>s[i];
	}
	for(int i=1;i<=n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	dfsInit(1);
	return 0;
}
