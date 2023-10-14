#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("adece.in");
ofstream fout("adece.out");

#define int long long
#define MOD 100000007

int fact[9002], inv[9002];

int binpow(int b, int e){
	int sol=1;
	while(e){
		if(e&1) sol=sol*b%MOD;
		b=b*b%MOD;
		e>>=1;
	}
	return sol;
}

void getfact(){
	int n=9000;
	fact[0]=1;
	for(int i=1;i<=n;++i) fact[i]=fact[i-1]*i%MOD;
	inv[n]=binpow(fact[n], MOD-2);
	for(int j=n-1;j>=0;--j) inv[j]=inv[j+1]*(j+1)%MOD;
}

int32_t main(){
	int a, b, c;
	cin>>a>>b>>c;
	int m=min({a, b, c});
	getfact();
	long long sol=0;
	for(int i=0;i<=m;++i){
		int total=a+b+c-2*i;
		int nr=fact[total]%MOD*inv[a-i]%MOD*inv[b-i]%MOD*inv[c-i]%MOD*inv[i]%MOD;
		if(i&1) sol=(sol+MOD-nr)%MOD;
		else sol=(sol+nr)%MOD;
	}
	cout<<sol%MOD<<"\n";
	return 0;
}