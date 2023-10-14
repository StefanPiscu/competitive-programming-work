#pragma optimize GCC("Ofast");
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define cin fin
#define cout fout
ifstream cin("pm2.in");
ofstream cout("pm2.out");

int n;
vector<int> cost;
vector<bool> used;
vector<vector<int>> in;
vector<vector<int>> out;
int sol=0;
vector<int> mincost;
vector<int> maxcost;

void init(int n){
	cost.resize(n+1);
	used.resize(n+1);
	in.resize(n+1);
	out.resize(n+1);
	mincost.resize(n+1);
	maxcost.resize(n+1);
}

vector<int> topsort;
void gettopsort(int x){
	if(used[x]) return;
	used[x]=1;
	for(auto it:in[x]) gettopsort(it);
	topsort.push_back(x);
}



int32_t main(){
	cin>>n;
	init(n);
	for(int i=1;i<=n;++i) cin>>cost[i];
	for(int i=1;i<=n;++i){
		int k;
		cin>>k;
		for(int j=1;j<=k;++j){
			int x;
			cin>>x;
			in[i].push_back(x);
			out[x].push_back(i);
		}
	}
	for(int i=1;i<=n;++i){
		gettopsort(i);
	}
	for(auto nod:topsort){
		mincost[nod]=0;
		for(auto it:in[nod]){
			mincost[nod]=max(mincost[nod], mincost[it]+cost[it]);
			if(mincost[nod]+cost[nod]>sol){
				sol=mincost[nod]+cost[nod];
			}
		}
	}
	reverse(topsort.begin(), topsort.end());
	for(auto nod:topsort){
		maxcost[nod]=sol-cost[nod];
		for(auto it:out[nod]){
			maxcost[nod]=min(maxcost[nod], maxcost[it]-cost[nod]);
		}

	}
	cout<<sol<<"\n";
	for(int i=1;i<=n;++i){
		cout<<mincost[i]<<" "<<maxcost[i]<<"\n";
	}
	return 0;
}