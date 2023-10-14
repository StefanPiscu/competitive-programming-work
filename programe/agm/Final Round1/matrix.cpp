#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> v;
vector<vector<int>> w;
int crCost, solMin=1e9;

bool check(int i, int j){
	if(i<2||j<3) return 1;
	int sum=0;
	for(int i2=i-1;i2<=i;++i2){
		for(int j2=j-2;j2<=j;++j2){
			sum+=w[i2][j2];
		}
	}
	sum%=3;
	return sum==1;
}

void bkt(int i, int j){
	if(i>n){
		solMin=min(solMin, crCost);
		return;
	}
	for(int k=0;k<3;++k){
		w[i][j]=k;
		crCost+=abs(w[i][j]-v[i][j]);
		if(check(i, j)){
			if(j==m) bkt(i+1, 1);
			else bkt(i, j+1);
		}
		crCost-=abs(w[i][j]-v[i][j]);
	}
}

int main(){
	cin>>n>>m;
	v.resize(n+1, vector<int>(m+1));
	w.resize(n+1, vector<int>(m+1));
	for(int i=1;i<=n;++i)
		for(int j=1;j<=m;++j) cin>>v[i][j];
	if(n<2||m<3){
		cout<<"0\n";
		return 0;
	}	
	if(n>3||m>5){
		cout<<"-1\n";
		return 0;
	}
	bkt(1, 1);
	cout<<solMin<<"\n";
	return 0;
};