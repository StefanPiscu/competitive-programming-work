#include <bits/stdc++.h>
using namespace std;

int t;

void solve(string &s){
	int n=s.size();
	s='$'+s;
	vector<int> v;
	v.push_back(0);
	int nr=0;
	for(int i=2;i<=n;++i){
		if(s[i]!=s[i-1]) v.push_back(s[i-1]);
	}
	v.push_back(s[n]);
	n=v.size()-1;
	vector<vector<int>> dp(n+3, vector<int>(n+3, 1e9));
	for(int i=1;i<=n;++i){
		dp[i][i]=2;
	}
	for(int l=1;l<=n;++l){
		for(int i=1;i+l-1<=n;++i){
			int j=i+l-1;
			if(i!=j&&v[i]==v[j]){
				dp[i][j]=min(dp[i][j], dp[i+1][j-1]+2);
			}
			dp[i][j]=min({dp[i][j], dp[i][j-1]+2, dp[i+1][j]+2});
			for(int k=i;k<j;++k){
				if(k!=i&&k!=j&&v[i]==v[k]&&v[k]==v[j]) dp[i][j]=min(dp[i][j], dp[i][k]+dp[k][j]-2);
				dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]);
			}
		}
	}
	cout<<dp[1][n]+s.size()-1<<"\n";
}

int main(){
	cin>>t;
	cin.ignore();
	while(t--){
		string s;
		getline(cin, s);
		solve(s);
	}
}