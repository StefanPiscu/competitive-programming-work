#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("numar2.in");
ofstream fout("numar2.out");

int main(){
	int n, m;
	cin>>n>>m;
	vector<int> v(n+1);
	vector<int> coef(n+1, 1);
	for(int i=1;i<=n;++i) cin>>v[i];

	while(m--){
		int minim = v[1]*coef[1];
		for(int i=1;i<=n;++i){
			minim=min(minim, v[i]*coef[i]);
		}
		for(int i=1;i<=n;++i){
			if(v[i]*coef[i]==minim) coef[i]++;	
		}
		if(m==0){
			cout<<minim<<"\n";
			return 0;
		}
	}
	return 0;
}