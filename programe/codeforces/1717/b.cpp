#include <bits/stdc++.h>
using namespace std;

// (i+j)%k=const
// (r+c)%k==const

int main(){
	int t;
	cin>>t;
	while(t--){
		int n, k, r, c;
		cin>>n>>k>>r>>c;
		int rest=(r-1+c-1)%k;
		for(int i=0;i<n;++i){
			for(int j=0;j<n;++j){
				if((i+j)%k==rest) cout<<'X';
				else cout<<'.';
			}
			cout<<"\n";
		}
	}
	return 0;
}