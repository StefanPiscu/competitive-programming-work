#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n, m;
		cin>>n>>m;
		multiset<int> v;
		for(int i=1;i<=n;++i){
			int x;
			cin>>x;
			v.insert(x);
		}
		for(int i=1;i<=m;++i){
			int x;
			v.erase(v.begin());
			cin>>x;
			v.insert(x);
		}
		long long sol=0;
		for(auto it:v) sol+=it;
		cout<<sol<<"\n";

	}
}