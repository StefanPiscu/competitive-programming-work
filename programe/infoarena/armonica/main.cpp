#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define cin fin
#define cout fout

ifstream fin("armonica.in");
ofstream fout("armonica.out");

int a, b, c;

int32_t main(){
	cin>>b;
	vector<pair<long long, long long>> sol;
	for(int a=b/2;a<b;++a){
		if(2*a==b) continue;
		if((1LL*a*b)%(2*a-b)!=0) continue; 
		long long c=(1LL*a*b)/(2*a-b);
		if(c<0) continue;
		sol.push_back({a, c});
		sol.push_back({c, a});

	}
	sol.push_back({b, b});
	cout<<sol.size()<<"\n";
	for(auto it:sol) cout<<it.first<<" "<<it.second<<"\n";
	return 0;
}
