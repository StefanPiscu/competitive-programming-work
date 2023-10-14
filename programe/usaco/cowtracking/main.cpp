#include <bits/stdc++.h>
using namespace std;

struct handshake{
	int t, a, b;
	bool operator<(const handshake &ot) const{
		return t<ot.t;
	}
}

int n, m;
vector<bool> cows;
vector<handshake> hs;

int main(){
	int n, m;
	cin>>n>>m;
	cows.resize(n+1);
	hs.resize(m+1);
	for(int i=1;i<=n;++i){
		char x;
		cin>>x;
		cows[i]=(x=='1');
	}
	for(int i=1;i<=m;++i){
		cin>>hs[i].t>>hs[i].a>>hs[i].b;
	}
	sort(hs.begin()+1, hs.end());
	for(int pz=1;pz<=n;++pz){
		for(int k=0;k<=m;++k){
			vector<int> fr(n+1, 0);
			for(int i=1;i<=m;++i){
				int a=hs[i].a, b=hs[i].b;
				if(fr[a]<fr[b]) swap(a, b);
				if(fr[a]>=k&&fr[b]==0) cout<<0;
			}
		}
	}
}