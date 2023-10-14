#include <bits/stdc++.h>
using namespace std;

int t;
bitset<32> fr;

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		fr.reset();
		for(auto it:s) fr[it-'a']=1;
		int count=fr.count();
		fr.reset();
		int nr=count;
		bool broken=0;
		for(int i=0;i<s.size();++i){
			if(s[i]!=s[i%count]){
				cout<<"NO\n";
				broken=1;
				break;
			}
		}
		if(!broken) cout<<"YES\n";
	}
}