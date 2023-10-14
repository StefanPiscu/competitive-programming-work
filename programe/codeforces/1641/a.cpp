#include <bits/stdc++.h>
using namespace std;

#define int long long

int n, x;
vector<int> v;

void solve(){
	cin>>n>>x;
	v.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>v[i];
	}
	sort(v.begin(), v.end());
	multiset<int> demanded;
	for(int i=1;i<=n;++i){
		if(demanded.count(v[i])){
			demanded.erase(demanded.find(v[i]));
		}
		else demanded.insert(v[i]*x);
	}
	cout<<demanded.size()<<"\n";
}

int32_t main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}