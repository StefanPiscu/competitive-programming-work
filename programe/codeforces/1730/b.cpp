#include <bits/stdc++.h>
using namespace std;

#define INF 1000000000

void solve(){
	int n;
	cin>>n;
	vector<int> x(n, 0), t(n, 0);
	for(int i=0;i<n;++i) cin>>x[i];
	for(int i=0;i<n;++i) cin>>t[i];
	int mini=x[0]+t[0], maxi=x[0]+t[0];
	for(int i=0;i<n;++i){
		mini=min({mini, x[i]+t[i], x[i]-t[i]});
		maxi=max({maxi, x[i]+t[i], x[i]-t[i]});
	}
	int val=mini+maxi;
	cout<<val/2;
	if(val%2) cout<<".5";
	cout<<"\n";
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}