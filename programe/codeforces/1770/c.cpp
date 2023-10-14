#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve(){
	int n;
	cin>>n;
	vector<int> v(n);
	map<int, int> mp;
	mp.clear();
	for(int i=0;i<n;++i) cin>>v[i];
	for(int i=0;i<n;++i){
		mp[v[i]]++;
		if(mp[v[i]]==2){
			cout<<"NO\n";
			return;
		}
	}
	for(int i=2;2*i<=n;++i){
		mp.clear();	
		int nr=i;
		for(auto it:v){
			mp[it%i]++;
			if(mp[it%i]==2) nr--;
		}
		if(nr==0){
			cout<<"NO\n";
			return;
		}
	}	
	cout<<"YES\n";
}

int32_t main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}