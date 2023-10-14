#include <bits/stdc++.h>
using namespace std;

#define int long long

#define MOD 1000000007

int bs, bd, bn;
int cs, cd, cn;

long long lcm(int a, int b){
	return 1LL*a*b/__gcd(a, b);
}

int solve(int ad){
	if(lcm(bd, ad)!=(long long)cd) return 0;
	int nr=cd/ad;
	return 1LL*nr*nr%MOD;
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		cin>>bs>>bd>>bn;
		cin>>cs>>cd>>cn;
		if((cs<bs)||(cs+1LL*cd*(cn-1))>(bs+1LL*bd*(bn-1))) cout<<0<<"\n";
		else if((cd%bd!=0)||((cs-bs)%bd!=0)) cout<<0<<"\n";
		else if(cs-cd<bs) cout<<-1<<"\n";
		else if(cs+1LL*cd*cn>bs+bd*(bn-1)) cout<<-1<<"\n";
		else{
			long long sol=0;
			for(int i=1;i*i<=cd;++i){
				int d1=i, d2=cd/i;
				sol+=solve(d1);
				sol%=MOD;
				if(d1!=d2) sol+=solve(d2), sol%=MOD;
			}
			cout<<sol<<"\n";
		}
	}
}
/*

*/