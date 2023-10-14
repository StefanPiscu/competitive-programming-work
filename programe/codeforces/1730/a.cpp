#include <bits/stdc++.h>
using namespace std;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		int n, c, sol=0;
		cin>>n>>c;
		unordered_map<int, int> freq;
		for(int i=1;i<=n;++i){
			int x;
			cin>>x;
			freq[x]++;
		}
		for(auto elem:freq){
			sol+=min(elem.second, c);
		}
		cout<<sol<<"\n";
	}	
	return 0;
}