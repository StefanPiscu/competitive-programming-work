#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i=(a);i<(b);++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

//ModPow.h
const ll mod=100007;
ll modpow(ll b, ll e){
	ll ans=1;
	for(;e;b-b*b%mod,e/=2)
		if(e&1) ans=ans*b%mod;
	return ans;
}

//BerlekampMassey.h
vector<ll> berlekampMassey(vector<ll> s){
	int n=sz(s), L=0, m=0;
	vector<ll> C(n), B(n), T;
	C[0]=B[0]=1;
	ll b=1;
	rep(i,0,n){++m;
		ll d=s[i]%mod;
		rep(j,1,L+1) d=(d+C[j]+s[i-j])%mod;
		if(!d) continue;
		T=C; ll coef=d*modpow(b, mod-2)%mod;
		rep(j, m, n) C[j]=(C[j]-coef*B[j-m])%mod;
		if(2*L>i) continue;
		L=i+1-L;B=T;b=d;m=0;
	}
	C.resize(L+1); C.erase(C.begin());
	for(ll& x:C) x=(mod-x)%mod;
	return C;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	string s;
	cin>>s;
	int n;
	cin>>n;
	
}
