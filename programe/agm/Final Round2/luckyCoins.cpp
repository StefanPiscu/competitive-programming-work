#include <bits/stdc++.h>
using namespace std;

#define int long long

int N, M, x, y;
long double dp[2002][2002];

long double getSol(int n, int m){
	if(n<0||m<0) return 0;
	if(dp[n][m]!=0)	return dp[n][m];
	long double tot=n+m;
	long double earned=(N-n)*x+(M-m)*y;
	if(tot==0) return dp[n][m]=earned;
	return dp[n][m]=max(earned, (n/tot)*getSol(n-1, m)+(m/tot)*getSol(n, m-1));
}

int32_t main(){
	cin>>N>>M>>x>>y;
	y=-y;
	cout<<setprecision(10)<<fixed<<getSol(N, M)<<"\n";
	return 0;
}