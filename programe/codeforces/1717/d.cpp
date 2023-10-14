#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

vector<int> fact, inv;

int binpow(int b, int e){
	int sol=1;
	while(e){
		if(e&1) sol=1LL*sol*b%MOD;
		b=1LL*b*b%MOD;
		e>>=1;
	}
	return sol;
}

void getfact(int n=100002){
	fact.resize(n+1);
	inv.resize(n+1);
	fact[0]=1;
	for(int i=1;i<=n;++i) fact[i]=1LL*fact[i-1]*i%MOD;
	inv[n]=binpow(fact[n], MOD-2);
	for(int i=n-1;i;--i){
		inv[i]=(1LL*inv[i+1]*(i+1))%MOD;
	}
}

int comb(int n, int k){
	if(k==n||k==0) return 1;
	return (1LL*((1LL*fact[n]*inv[k])%MOD)*inv[n-k])%MOD;
}

int main(){
	int n, k;
	cin>>n>>k;
	getfact();
	if(k>n) k=n;
	int sol=0;
	for(int i=0;i<=k;++i){
		sol=(1LL*sol+comb(n, i))%MOD;
	}
	cout<<sol<<"\n";
	return 0;
}