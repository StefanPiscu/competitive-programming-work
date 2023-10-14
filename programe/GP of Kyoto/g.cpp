#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
vector<int> per, a, b;
vector<bool> used;


long long solve(vector<int> elems){
	if(elems.size()==1) return 0;
	//reverse(elems.begin(), elems.end());
	long long sol=1e15;
	vector<vector<vector<long long>>> dp(elems.size(), vector<vector<long long>>(2, vector<long long>(2, 1e15)));
	dp[0][0][0]=0;
	dp[0][1][1]=a[elems[0]];
	for(int i=1;i<elems.size();++i){
		for(int h=0;h<=1;++h){
			for(int h2=0;h2<=1;++h2){
				for(int h3=0;h3<=1;++h3){
					dp[i][h][h3]=min(dp[i][h][h3], dp[i-1][h][h2]+h3*a[elems[i]]+((h2==0)||(h3==0))*b[elems[i]]);
				}
			}
		}
	}
	/*
	for(int i=0;i<elems.size();++i){
		for(int h=0;h<=1;++h){
			for(int h2=0;h2<=1;++h2){
					cout<<i<<" "<<h<<" "<<h2<<" "<<dp[i][h][h2]<<"\n";
			}
		}
	}
	*/
	for(int h=0;h<=1;++h){
		for(int h2=0;h2<=1;++h2){
			sol=min(sol, dp[elems.size()-1][h][h2]+b[elems[0]]*((h2==0)||(h==0)));
		}
	}
	/*
	for(int i=0;i<elems.size();++i){
		cout<<elems[i]<<" "<<a[elems[i]]<<" "<<b[elems[i]]<<"\n";
	}
	cout<<sol<<"*\n";
	*/
	return sol;
}

int32_t main(){
	cin>>n;
	per.resize(n+1);
	a.resize(n+1);
	b.resize(n+1);
	used.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>per[i];
	}
	for(int i=1;i<=n;++i){
		cin>>a[i];
	}
	for(int i=1;i<=n;++i){
		cin>>b[i];
	}
	long long ans=0;
	for(int i=1;i<=n;++i){
		if(used[i]) continue;
		vector<int> cycle;
		int cr=i;
		while(!used[cr]){
			cycle.push_back(cr);
			used[cr]=1;
			cr=per[cr];
		}
		ans+=solve(cycle);
	}
	cout<<ans<<"\n";
	return 0;
}
