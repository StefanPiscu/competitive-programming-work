#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("summax.in");
ofstream fout("summax.out");

int cer;
int n, st, dr;
int a[2002][2002];

struct elem{
	int maxi;
	long long nr, val;
};

elem dp[2002][2002];

void show(int x, int i=1, int j=1){
	if(i>n) return;
	cout<<j<<" ";
	if(dp[i][j].val>=x) show(x, i+1, j);
	else show(x-dp[i][j].val, i+1, j+1);
}

int main(){
	cin>>cer;
	cin>>n>>st>>dr;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=i;++j){
			cin>>a[i][j];
		}
	}
	for(int i=1;i<=n;++i){
		dp[n][i].maxi=a[n][i];
		dp[n][i].nr=1;
	}
	for(int i=n-1;i;--i){
		for(int j=1;j<=i;++j){
			if(dp[i+1][j].maxi==dp[i+1][j+1].maxi){
				dp[i][j].maxi=dp[i+1][j].maxi;
				dp[i][j].nr=dp[i+1][j].nr+dp[i+1][j+1].nr;
				dp[i][j].val=dp[i+1][j].nr;
			}
			else if(dp[i+1][j].maxi>dp[i+1][j+1].maxi){
				dp[i][j].maxi=dp[i+1][j].maxi;
				dp[i][j].nr=dp[i+1][j].nr;
				dp[i][j].val=dp[i+1][j].nr;
			}
			else{
				dp[i][j].maxi=dp[i+1][j+1].maxi;
				dp[i][j].nr=dp[i+1][j+1].nr;
			}
			dp[i][j].maxi+=a[i][j];
			dp[i][j].nr=min(2000000001ll, dp[i][j].nr);
			dp[i][j].val=min(2000000001ll, dp[i][j].val);
		}
	}
	if(cer==1){
		/*
		for(int i=1;i<=n;++i){
			for(int j=1;j<=i;++j){
				cout<<dp[i][j].nr<<" ";
			}
			cout<<"\n";
		}
		*/
		cout<<dp[1][1].nr<<"\n";
	}
	else{
		for(int i=st;i<=dr;++i){
			show(i);
			cout<<"\n";
		}
	}
}