#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int bal=0;
		if(s[s.size()-1]!='B'){
			cout<<"NO\n";
			continue;
		}
		int isOk=1;
		for(int i=0;i<s.size();++i){
			if(s[i]=='B') bal--;
			else bal++;
			if(bal<0){
				cout<<"NO\n";
				isOk=0;
				break;
			}
		}
		if(isOk) cout<<"YES\n";
	}
}