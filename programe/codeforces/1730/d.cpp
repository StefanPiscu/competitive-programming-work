#include <bits/stdc++.h>
using namespace std;

bool solve(){
	int n;
	cin>>n;
	string s1, s2;
	cin>>s1>>s2;
	reverse(s2.begin(), s2.end());
	map<pair<char, char>, int> mp;
	bool odd=(n%2);
	for(int i=0;i<n;++i){
		if(s1[i]>s2[i]) swap(s1[i], s2[i]);
		mp[{s1[i], s2[i]}]++;
	}
	for(auto it:mp){
		if(it.second%2){
			if(it.first.first==it.first.second&&odd) odd=0;
			else return 0;
		}
	}
	return odd==0;
}


int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin>>t;
	while(t--){
		if(solve()) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}

