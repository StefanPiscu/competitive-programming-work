#include <bits/stdc++.h>
using namespace std;

#define int long long

int32_t main(){
	int t;
	cin>>t;
	vector<pair<int, int>> v(t+1);
	vector<int> sol(t+1);
	for(int i=1;i<=t;++i) cin>>v[i].first, v[i].second=i;
	sort(v.begin()+1, v.end());
	int p=1;
	int valTot=0;
	for(int i=1;(i-1)*(i-1)<=v[t].first;++i){
		int val=i*i;
		while(p<=t&&v[p].first<(1LL*(i+1)*(i+1))){
			sol[v[p].second]+=valTot+(v[p].first-(i*i)+1)*i;
			p++;
		}
		valTot+=((i+1)*(i+1)-i*i)*i;
	}
	for(int i=1;i<=t;++i){
		cout<<sol[i]<<"\n";
	}
	return 0;
}