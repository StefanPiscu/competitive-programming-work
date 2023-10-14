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

int n, p;
vector<pair<int, int>> v;
vector<long double> val;
vector<bool> used;
	vector<int> org;
	vector<vector<int>> out;

	void solve(){
		cin>>n;
		v.resize(n+1);
		for(int i=1;i<min(n+1, (int)val.size());++i){
			val[i]=1e9;
		}
		val.resize(n+1, 1e9);
		org.clear();
		org.resize(n+1, 0);
		for(int i=1;i<min(n+1, (int)out.size());++i){
			out[i].clear();
		}
		out.resize(n+1);
		used.clear();
		used.resize(n+1, 0);
		for(int i=1;i<=n;++i){
			cin>>v[i].first>>v[i].second;
		}

		int nr=n;
		val[1]=0;
		long double sol=0;
		while(nr--){
			int mini=0;
			for(int i=1;i<=n;++i){
				if(used[i]) continue;
				if(val[i]<val[mini]) mini=i;
			}
			if(org[mini]){
				sol+=val[mini];
				out[mini].push_back(org[mini]);
				out[org[mini]].push_back(mini);
			}
			//cout<<mini<<" "<<val[mini]<<" "<<org[mini]<<endl;
			used[mini]=1;
			for(int i=1;i<=n;++i){
				if(used[i]) continue;
				long double newVal=dist(v[i], v[mini]);
				if(val[i]>newVal){
					val[i]=newVal;
					org[i]=mini;
				}
			}
		}
		if(p==1){
			cout<<fixed<<setprecision(10)<<sol<<"\n";
			return;
		}
		function<void(int, int)> dfs = [&](int x, int fat){
			sort(out[x].begin(), out[x].end(), [&](int a, int b){
				return abs(x-a)<abs(x-b);
			});
			for(auto it:out[x]){
				if(it==fat) continue;
				dfs(it, x);
			}	
			if(fat) cout<<x<<" "<<fat<<"\n";
		};
		dfs(1, 0);
	}	
};


int main(){
	int p;
	cin>>p;
	int t;
	cin>>t;
	solver x;
	x.p=p;
	while(t--){
		x.solve();
	}
	return 0;
}