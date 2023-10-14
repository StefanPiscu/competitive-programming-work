#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("oracol.in");
ofstream fout("oracol.out");


int c[1002][1002];
int minDist[1002];
bool used[1002];

int main(){
	int n;
	cin>>n;
	for(int i=1;i<=n;++i){
		minDist[i]=1e9;
		for(int j=i+1;j<=n+1;++j){
			cin>>c[i][j];
			c[j][i]=c[i][j];
		}
	}
	minDist[n+1]=1e9;
	minDist[1]=0;
	int sol=0;
	for(int i=1;i<=n+1;++i){
		int minPoz=0, mini=1e9;
		for(int j=1;j<=n+1;++j){
			if(used[j]) continue;
			if(minDist[j]<mini) minPoz=j, mini=minDist[j];
		}
		sol+=mini;
		used[minPoz]=1;
		for(int j=1;j<=n+1;++j){
			if(used[j]) continue;
			minDist[j]=min(minDist[j], c[minPoz][j]);
		}
	}
	cout<<sol<<"\n";
}