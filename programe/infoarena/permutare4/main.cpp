#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
#define int long long
ifstream fin("permutare4.in");
ofstream fout("permutare4.out");

// number of sequences with i brackets, and j extra closing brackets
int dp[2002][2002];

void solve1(){
	int n, p;
	cin>>n>>p;
	n=2*n;
	int nro=0;
	string sol;
	for(int i=1;i<=n;++i){
		int valo=dp[n-i][nro+1];
		if(valo>=p){
			nro++;
			sol+='(';
		}
		else{
			nro--;
			p-=valo;
			sol+=')';
		}
	}
	vector<int> ans;
	for(int i=0;i<n;++i){
		if(sol[i]=='(') ans.push_back(i+1);
	}
	for(int i=0;i<n;++i){
		if(sol[i]==')') ans.push_back(i+1);
	}
	for(auto it:ans) cout<<it<<" ";
	cout<<"\n";
}

void solve2(){
	int n; 
	cin>>n;
	string s;
	for(int i=0;i<=2*n;++i) s+='(';
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		s[x]='(';
	}
	for(int i=1;i<=n;++i){
		int x;
		cin>>x;
		s[x]=')';
	}
	n=2*n;
	int bal=0;
	int sol=0;
	for(int i=1;i<=n;++i){
		if(s[i]==')'){
			sol+=dp[n-i][bal+1];
			bal--;
		}
		else bal++;
	}
	cout<<sol+1<<"\n";
}

int32_t main(){
	int n=2000;
	dp[0][0]=1;
	for(int i=1;i<=n;++i){
		for(int j=0;j<=i;++j){
			if(j) dp[i][j]+=dp[i-1][j-1];
			dp[i][j]+=dp[i-1][j+1];	
			if(dp[i][j]>1e12) dp[i][j]=1e12;
		}
	}
	int x;
	int line=0;
	while(cin>>x){
		if(x==1) solve1();
		else solve2();
	}
}