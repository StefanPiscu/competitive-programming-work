#include <bits/stdc++.h>
using namespace std;

#define int long long

int t;

int32_t main(){
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		vector<int> p(n+1);
		for(int i=1;i<=n;++i) p[i]=i;
		swap(p[1], p[n]);
		vector<pair<int, int>> sol;
		long long ans=0;
		sol.push_back({1, n});
		ans+=(n-1)*(n-1);
		for(int i=2,j=n-1;i<=j;++i, --j){
			if(i==j){
				swap(p[1], p[j]);
				sol.push_back({j, 1});
				ans+=(j-1)*(j-1);
			}
			else{
				swap(p[i], p[n]);	
				sol.push_back({i, n});
				ans+=(n-i)*(n-i);
				swap(p[j], p[1]);
				sol.push_back({j, 1});
				ans+=(j-1)*(j-1);
			}
		}
		cout<<ans<<"\n";
		for(int i=1;i<=n;++i){
			cout<<p[i]<<" ";	
		}
		cout<<"\n";
		cout<<sol.size()<<"\n";
		reverse(sol.begin(), sol.end());
		for(auto it:sol) cout<<it.first<<" "<<it.second<<"\n";
	}
	return 0;
}