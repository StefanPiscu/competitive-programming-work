#include <bits/stdc++.h>
using namespace std;

void solve(int n, int k){
	int maxi=n, mini=1;
	int i;
	for(i=1;i<=n;++i){
		for(int j=1;i<=n&&j<k;++j,++i){
			cout<<maxi<<" ";
			maxi--;
		}
		if(i<=n){
			cout<<mini<<" ";
			mini++;
		}
	}
	cout<<"\n";
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		int n, m;
		cin>>n>>m;
		solve(n, m);
	}
}