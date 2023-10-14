#include <bits/stdc++.h>
using namespace std;


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int t;
	cin>>t;
	for(int i=1;i<=t;++i){

		int n;
		cin>>n;
		cout<<2*(n/3+n/2)+n<<"\n";
	}
	return 0;
}