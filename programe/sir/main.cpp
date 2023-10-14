#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<int> v, sp;
vector<int> frst;

int main(){
	cin>>n;
	v.resize(n+2);
	sp.resize(n+2);
	frst.resize(n+2);
	int nr=0;
	for(int i=1;i<=n;++i){
		cin>>v[i];
		if(v[i]!=0) nr++;
		sp[i]=sp[i-1]+bool(v[i]);
	}
	n++;
	v[n]=(nr%2)*(nr+1);
	sp[n]=sp[n-1]+bool(v[n]);
	frst[n]=nr+1;
	for(int i=n-1;i;--i){
		if(v[i]!=0) frst[i]=v[i];
		else frst[i]=frst[i+1];
	}
	while(q--){
		int l, r;
	}
}