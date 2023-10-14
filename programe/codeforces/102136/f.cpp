#include <bits/stdc++.h>
using namespace std;

int n, m;
bool canSort[1<<15];
long long dp[1<<15];


bool isSorted(int mask){
	bool ok=0;
	for(int i=0;i<n;++i){
		if(bool(mask&(1<<i))!=ok){
			if(ok) return 0;
			ok=1;
		}
	}
	return 1;
}

int main(){
	cin>>n>>m;
	vector<pair<int, int>> qrys;
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		qrys.push_back({a-1, b-1});
	}
	for(int i=0;i<(1<<n);++i){
		int mask=i;
		for(auto it:qrys){
			bool bit1=mask&(1<<it.first), bit2=mask&(1<<it.second);
			if(bit1>bit2){
				mask^=(1<<it.second);
				mask^=(1<<it.first);
			}
		}
		//cout<<bitset<3>(i)<<" "<<bitset<3>(mask)<<" "<<isSorted(mask)<<"*\n";
		canSort[i]=isSorted(mask);
	}
	dp[0]=1;

	for(int mask=0;mask<(1<<n);++mask){
		if(!canSort[mask]) continue;
		//cout<<bitset<3>(mask)<<"\n";
		for(int bit=mask&-mask,aux=mask;bit;aux^=bit,bit=aux&-aux){
			if(!canSort[mask^bit]) continue;
			dp[mask]+=dp[mask^bit];
			//cout<<bitset<3>(mask^bit)<<" "<<dp[mask^bit]<<"\n";
		}
	}
	long long fact=1;
	for(int i=1;i<=n;++i) fact*=i;
	cout<<fact-dp[(1<<n)-1]<<"\n";
	return 0;
}