#include <bits/stdc++.h>
using namespace std;


bool solve(){
	int n;
	cin>>n;
	vector<int> a(n), b(n);
	for(int i=0;i<n;++i) cin>>a[i];
	for(int i=0;i<n;++i) cin>>b[i];
	a.push_back(a[0]);
	b.push_back(b[0]);
	for(int i=0;i<n;++i){
		if(b[i]<a[i]) return 0;
		if(b[i]>a[i]&&b[i]>b[i+1]+1) return 0;
	}
	return 1;
}

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	while(t--){
		if(solve()) cout<<"YES\n";
		else cout<<"NO\n";
	}
}