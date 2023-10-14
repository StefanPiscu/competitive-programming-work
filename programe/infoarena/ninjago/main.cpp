#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("ninjago.in");
ofstream fout("ninjago.out");

int c;
int n, m;

struct edge{
	int a, b;
	pair<int, int> cost;

	friend bool operator<(const edge& a, const edge& ot){
		if(a.cost.first==0&&ot.cost.first!=0) return 1;
		else if(a.cost.first!=0&&ot.cost.first==0) return 0;
		return a.cost<ot.cost;
	}
};


vector<edge> edges;

vector<int> fat, sz;

int get(int x){
	if(fat[x]==x) return x;
	return fat[x]=get(fat[x]);
}

int szmax=1;
int nre=0, nrce=0;
int sol=0;

void join(int a, int b, pair<int, int> cost){
	//int ora=a, orb=b;
	a=get(a), b=get(b);
	if(a==b) return;
	//cout<<ora<<" "<<orb<<" "<<cost.first<<" "<<cost.second<<"\n";
	nrce+=bool(cost.first), nre+=cost.first, sol+=cost.second;
	if(sz[a]<sz[b]) swap(a, b);
	fat[b]=a;
	sz[a]+=sz[b];
	szmax=max(szmax, sz[a]);
}

int main(){
	cin>>c;
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		int a, b;
		cin>>a>>b;
		pair<int, int> cost;
		string s;
		cin>>s;
		int pow=1;
		for(int i=0;i<4;++i){
			if(s[i]=='E') cost.first++;
			else{
				int x=s[i]-'A'+1;
				cost.second+=pow*x;
			}
				pow*=5;
		}
		edges.push_back({a, b, cost});
	}
	sort(edges.begin(), edges.end());
	fat.resize(n+1);
	sz.resize(n+1);
	for(int i=1;i<=n;++i) fat[i]=i, sz[i]=1;
	if(c==1){
		for(auto it:edges){
			if(it.cost.first>0) break;
			join(it.a, it.b, it.cost);
		}
		cout<<sz[get(1)]<<"\n";
	}	
	else{
		for(auto it:edges){
			join(it.a, it.b, it.cost);
		}
		if(c==2){
			cout<<nrce<<"\n"<<nre<<"\n";
		}
		else{
			cout<<sol<<"\n";
		}
	}
	return 0;
}
