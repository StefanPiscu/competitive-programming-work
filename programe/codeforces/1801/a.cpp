#include <bits/stdc++.h>
using namespace std;

int t;
void solve(){
	int n, m;
	cin>>n>>m;
	cout<<n*m<<"\n";
	random_device r;
	mt19937 generator(r());
	uniform_int_distribution<long long> distrib(0, 1LL<<63);
	vector<long long> lins(n+1), cols(m+1);
	for(int i=1;i<=n;++i) lins[i]=distrib(generator);
	for(int i=1;i<=m;++i) cols[i]=distrib(generator);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			cout<<(lins[i]^cols[j])<<" ";
		}
		cout<<"\n";
	}
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}