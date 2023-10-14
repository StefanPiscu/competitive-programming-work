#include <bits/stdc++.h>
using namespace std;

int n;
vector<bool> deleted;
vector<int> a[3];
vector<int> fr[3];
vector<int> rev;
queue<int> q;

int main(){
	cin>>n;
	for(int i=0;i<3;++i){
		a[i].resize(n+1, 0);
		fr[i].resize(n+1, 0);
	}
	deleted.resize(n+1);
	rev.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>a[0][i];
		rev[a[0][i]]=i;
	}
	for(int i=1;i<3;++i){
		for(int j=1;j<=n;++j){
			cin>>a[i][j];
			fr[i][a[i][j]]++;
		}
	}
	for(int i=1;i<3;++i){
		for(int j=1;j<=n;++j){
			if(fr[i][j]==0){
				q.push(rev[j]);
			}
		}
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		if(deleted[x]) continue;
		deleted[x]=1;
		for(int i=1;i<3;++i){
			fr[i][a[i][x]]--;
			if(fr[i][a[i][x]]==0) q.push(rev[a[i][x]]);
		}
	}
	int nr=0;
	for(int i=1;i<=n;++i) nr+=deleted[i];
	cout<<nr<<"\n";
	return 0;
}