#include <bits/stdc++.h>
using namespace std;

vector<string> first={"suruas"};
vector<string> second={"rotpar", "spotarec", "nodo", "xyretp", "sumim"};

int main(){
	int n;
	int a=0, b=0, c=0;
	cin>>n;
	while(n--){
		string s;
		cin>>s;
		reverse(s.begin(), s.end());
		int done=0;
		for(auto it:first){
			if(s.size()<it.size()) continue;
			int ok=1;
			for(int i=0;i<it.size();++i){
				if(it[i]!=s[i]){
					ok=0;
					break;
				}	
			}
			if(ok){
				a++;
				done=1;
				break;
			}
		}
		if(done) continue;
		for(auto it:second){
			if(s.size()<it.size()) continue;
			int ok=1;
			for(int i=0;i<it.size();++i){
				if(it[i]!=s[i]){
					ok=0;
					break;
				}	
			}
			if(ok){
				b++;
				done=1;
				break;
			}
		}
		if(done) continue;
		c++;
	}
	cout<<a<<" "<<b<<" "<<c<<"\n";
}