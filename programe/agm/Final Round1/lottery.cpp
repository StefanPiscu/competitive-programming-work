#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, k;
vector<pair<int, int>> v;
vector<long double> sa;

int32_t main(){
	cin>>n>>k;
	v.resize(n+1);
	sa.resize(n+1);
	long double W=0;
	for(int i=1;i<=n;++i) cin>>v[i].first>>v[i].second, W+=v[i].second;
	long double sol=0;
	for(int i=1;i<=n;++i){
		sol+=v[i].first*(v[i].second/W);
	}
	sort(v.begin()+1, v.end());
	sa[n]=v[n].first;
	long double crw=v[n].second;
	for(int i=n-1;i;--i){
		sa[i]=sa[i+1]*crw;
		crw+=v[i].second;
		sa[i]=sa[i]/crw+v[i].first*(v[i].second/crw);
	}
	/*
	for(int i=1;i<=n;++i) cout<<sa[i]<<" ";
	cout<<"\n";
	*/
	int cr=1;
	int lW=0, hW=W;
	while(k--){
		while(cr<n&&v[cr].first<=sol) hW-=v[cr].second, lW+=v[cr].second, cr++;
		sol=sol*lW/W+sa[cr]*hW/W;
	}
	cout<<fixed<<setprecision(10)<<sol<<"\n";
	return 0;
}