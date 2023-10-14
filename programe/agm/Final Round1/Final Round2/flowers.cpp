#include <bits/stdc++.h>
using namespace std;

#define NMAX 3003
#define int long long

int n;
bool v[NMAX][NMAX];
int up[NMAX][NMAX];
int down[NMAX][NMAX];
int lef[NMAX][NMAX];
int righ[NMAX][NMAX];
int behind[NMAX][NMAX];
int ahead[NMAX][NMAX];

struct FenwickTree{
	int n;
	vector<int> v;	
	FenwickTree(int _n){
		n=_n+1;
		v.resize(n+1, 0);
	}

	void update(int x, int val){
		for(;x<=n;x+=(x&-x)){
			v[x]+=val;
		}
	}

	int query(int x){
		int sol=0;
		for(;x;x-=(x&-x)){
			sol+=v[x];
		}
		return sol;
	}

	int query(int l, int r){
		if(l==0) return query(r);
		return query(r)-query(l);
	}

};

int32_t main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j) cin>>v[i][j];
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(v[i][j]){
				up[i][j]=1+up[i-1][j];
				lef[i][j]=1+lef[i][j-1];
			}
			behind[i][j]=min(up[i][j], lef[i][j]);
		}
	}
	for(int i=n;i;--i){
		for(int j=n;j;--j){
			if(v[i][j]){
				down[i][j]=1+down[i+1][j];
				righ[i][j]=1+righ[i][j+1];
			}
			ahead[i][j]=min(down[i][j], righ[i][j]);
		}
	}
	long long sol=0;
	for(int diag=1-n;diag<=n-1;++diag){
		//sol=0;
		int first=0, second=0;
		if(diag<=0) first=1, second=first-diag;
		else second=1, first=diag+1;
		int index=1;
		FenwickTree aib(n+1);
		priority_queue<pair<int, int>> pq;
		while(second<=n&&first<=n){
			//cout<<first<<" "<<second<<" "<<ahead[first][second]<<" "<<behind[first][second]<<" "<<index<<"*\n";
			if(v[first][second]==0){
				second++, first++, index++;
				continue;
			}
			/*
			if(second==1&&first==1){
				cout<<"*\n";
			}
			*/
			while(!pq.empty()&&(-pq.top().first<=index)){
				int x=pq.top().second;
				//deactivate x
				aib.update(x, -1);

				pq.pop();
			}
			pq.push({-(index+ahead[first][second]), index});
			//activate index
			aib.update(index, 1);

			//evaluate back
			sol+=aib.query(index-behind[first][second], index);


			second++, first++, index++;
		}
		//cout<<diag<<" "<<sol<<"\n";
	}
	cout<<sol<<"\n";
	return 0;
}