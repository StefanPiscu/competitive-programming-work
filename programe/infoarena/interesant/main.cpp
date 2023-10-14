#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace	std;

ifstream fin("interesant.in");
ofstream fout("interesant.out");

#define cin fin
#define cout fout

bool check(string &a, string &b){
	if(a.size()>=b.size()) return 0;
	int p=0;
	for(int i=0;i<b.size();++i){
		if(b[i]==a[p]) p++;
		if(p==a.size()) return 1;
	}
	return 0;
}

string v[202];

int main(){
	int c, n;
	cin>>c>>n;
	string best;
	for(int i=1;i<=n;++i){
		cin>>v[i];
		if(v[i].size()>best.size()) best=v[i];
		else if(v[i].size()==best.size()&&best<v[i]) best=v[i];
	}
	if(c==1) cout<<best<<"\n";
	else{
		vector<bool> used(n+1);
		int nr=n;
		for(int i=1;i<=n;++i){
			if(used[i]) continue;
			for(int j=1;j<=n;++j){
				if(used[j]) continue;
				if(check(v[i], v[j])){
					used[i]=1;
					nr--;
					break;
				}
			}
		}
		cout<<nr<<"\n";
		for(int i=1;i<=n;++i){
			if(!used[i]) cout<<v[i]<<"\n";
		}
	}
	return 0;
}