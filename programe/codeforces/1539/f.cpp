#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("poligon7.in");
ofstream fout("poligon7.out");

#define sqr(x) ((x)*(x))

long double dist(pair<int, int> a, pair<int, int> b){
	return sqrt((long double)sqr(a.first-b.first)+(long double)sqr(a.second-b.second));
}

struct solver{
	int n, p;
	vector<pair<int, int>> v;
	vector<long double> val;
	vector<int> org;
	vector<vector<int>> out;

	void solve(){
		cin>>n;
		v.resize(n+1);
		val.resize(n+1, 1e9);
		org.resize(n+1, 0);
		out.resize(n+1);
		for(int i=1;i<=n;++i){
			cin>>v[i].first>>v[i].second;
		}

		int nr=n-1;
		val[1]=0;
		long double sol=0;
		while(nr--){
			int mini=1;
			for(int i=2;i<=n;++i){
				if(val[mini]==-1) continue;
				if(val[i]<val[mini]) mini=i;
			}
			if(org[mini]){
				sol+=val[mini];
				out[mini].push_back(org[mini]);
				out[org[mini]].push_back(mini);
			}
			for(int i=1;i<=n;++i){
				if(val[i]==-1||i==mini) continue;
				int newVal=dist(v[i], v[mini]);
				if(val[i]>newVal){
					val[i]=newVal;
					org[i]=mini;
				}
			}
			val[mini]=-1;
		}
		if(p==1){
			cout<<fixed<<setprecision(10)<<sol<<"\n";
			return;
		}
		function<void(int, int)> dfs = [&](int x, int fat){
			for(auto it:out[x]){
				if(it==fat) continue;
				dfs(it, x);
			}	
			cout<<x<<" "<<fat<<"\n";
		};
		dfs(1, 0);
	}	
};


int main(){
	int p;
	int t;
	cin>>t;
	while(t--){
		solver *x=new solver;
		x->p=p;
		x->solve();
		delete x;
	}
	return 0;
}