#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	cin>>s;
	int drx=0, t1=0;
	for(int i=0;i<5;++i){
		if(s[i]=='D') drx++;
		else if(s[i]=='T') t1++;
	}
	if(drx>=3) cout<<"DRX"<<"\n";
	else if(t1>=3) cout<<"T1"<<"\n";
}