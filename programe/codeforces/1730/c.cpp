#include <bits/stdc++.h>
using namespace std;

void solve(){
	string s, sol;
	cin>>s;
	int mini=s[s.size()-1];
	for(int i=s.size()-1;i>=0;--i){
		if(s[i]>mini) s[i]=min((int)'9', s[i]+1);
		mini=min(mini, int(s[i]));
	}	
	sort(s.begin(), s.end());
	cout<<s<<"\n";
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}