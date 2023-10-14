#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin>>t;
	while(t--){
		string s;
		cin>>s;
		int score=0;
		for(auto it:s) score+=it-'a'+1;
		if(s.size()%2==0){
			cout<<"Alice "<<score<<"\n";	
		}
		else{
			score-=((min(s[0], s[s.size()-1])-'a'+1)*2);
			if(score<0) cout<<"Bob "<<-score<<"\n";
			else cout<<"Alice "<<score<<"\n";
		}
	}
}