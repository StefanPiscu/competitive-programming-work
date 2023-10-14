#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	int cr=1e9;
	while(t--){
		int n;
		cin>>n;
		vector<int> v(n+1);
		for(int i=1;i<=n;++i) cin>>v[i];
		int eqal=0;
		for(int i=2;i<=n;++i){
			if(v[i]==v[i-1]) eqal++;
		}
		if(eqal<=1){
			cout<<"0\n";
			continue;
		}
		int nr=0;
		for(int i=2;i<n;++i){
			if(v[i]==v[i-1]){
				nr++;
				if(v[i]==v[i+1]) eqal--;
				if((i+1<n)&&v[i+1]==v[i+2]) eqal--;
				v[i]=v[i+1]=cr++;
				if(eqal<=1) break;
			}
		}
		cout<<nr<<"\n";
	}
}