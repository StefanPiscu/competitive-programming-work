#include <bits/stdc++.h>
using namespace std;

char sol[502][502];

void solve(int n, bool t=0){
	if(n==0) return;
	for(int i=1;i<=n;++i){
		if(t){
			sol[n][i]='B';
			sol[i][n]='W';
		}
		else{
			sol[i][n]='B';
			sol[n][i]='W';
		}
	}
	solve(n-1, !t);
};

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			sol[i][j]='W';
		}
	}
	solve(n);
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cout<<sol[i][j];
		}
		cout<<"\n";
	}
}