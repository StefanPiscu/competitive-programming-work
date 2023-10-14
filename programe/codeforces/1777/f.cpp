#include <bits/stdc++.h>
using namespace std;

struct Trie{
	Trie* nx[2];

	Trie(){
		nx[0]=nx[1]=nullptr;
	}

	void add(int val, int bit){
		if(bit==-1) return;
		bool x=val&(1<<bit);
		if(nx[x]==nullptr) nx[x]=new Trie;
		nx[x]->add(val, bit-1);
	}

	int getminxor(int val, int bit){
		if(bit==-1) return;
		bool x=val&(1<<bit), y=0;
		if(nx[x]==nullptr) x!=1, y=1;
		return y<<bit+getmin(val, bit-1);
	}

}

int rmq[32][200000];
vector<int> v(n);
vector<int> xorPartial(n);

int lg(int x){
	return 31-__builtin_clz(x);
}

int getMax(int l, int r){
	int k=lg(r-l+1);
	if(v[rmq[k][l]]>v[rmq[k][r-(1<<k)+1]]) return rmq[k][l];
	return rmq[k][r-(1<<k)+1];
}

int getXor(int l, int r){
	if(l==0) return xorPartial[r];
	return xorPartial[r]^xorPartial[l];
}


void solve(){
	int n;
	cin>>n;
	v.resize(n);
	xorPartial.resize(n);
	for(int i=0;i<n;++i) cin>>v[i];
	xorPartial[0]=v[0]; for(int i=1;i<n;++i) xorPartial[i]=xorParital[i-1]^v[i];
	for(int i=0;i<n;++i) rmq[0][i]=i;
	for(int j=1;j<32;++j){
		for(int i=0;i+(1<<j)-1<n;++j){
			if(v[rmq[j-1][i]]>=v[rmq[j-1][i+(1<<(j-1))]]) rmq[j][i]=rmq[j-1][i];
			else rmq[j][i]=rmq[j-1][i+1<<(j-1)];
		}
	}
}

Trie* divideAndCounqer(int l, int r){
	Trie* ret=nullptr;
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}