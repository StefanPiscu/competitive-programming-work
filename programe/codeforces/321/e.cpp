#include <bits/stdc++.h>
using namespace std;

int n, k;
long long sp[4002][4002];
int dp[802][4002];

int cost(int l, int r){
	return sp[r][r]-sp[l-1][r]-sp[r][l-1]+sp[l-1][l-1];
}

void computeLayer(int layer, int l, int r, int optl, int optr){
	int mid=(l+r)/2;
	int opt=optl;
	int best=dp[layer-1][opt-1]+cost(opt, mid);
	for(int i=optl+1;i<=optr&&i<=mid;++i){
		int val=dp[layer-1][i-1]+cost(i, mid);
		if(val<best){
			opt=i;
			best=val;
		}
	}
	dp[layer][mid]=best;
	if(l<mid) computeLayer(layer, l, mid-1, optl, opt);
	if(mid<r) computeLayer(layer, mid+1, r, opt, optr); 
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n>>k;
	cin.get();
	for(int i=1;i<=n;++i){
		char *line=new char[8002];
		cin.getline(line, 8002);
		for(int j=1;j<=n;++j){
			sp[i][j]=sp[i-1][j]+sp[i][j-1]-sp[i-1][j-1]+(line[j*2-2]-'0');
		}
		delete line;
	}
	for(int i=1;i<=n;++i) dp[0][i]=(1<<30);
	for(int i=1;i<=k;++i){
		computeLayer(i, 1, n, 1, n);
	}
	cout<<dp[k][n]/2<<"\n";
	return 0;
}