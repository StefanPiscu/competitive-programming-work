#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("connect.in");
ofstream fout("connect.out");

struct DSUQ{
	vector<int> fat, sz;
	int nrComp;

	DSUQ(int n){
		fat.resize(n+1);
		sz.resize(n+1);
		for(int i=1;i<=n;++i) fat[i]=i, sz[i]=1;
		nrComp=n;
	}
	struct undoData{
		int a, b;
		int fatb, sza;
		int nrComp;
	};
	stack<undoData> undoStack;

	int getfat(int x){
		if(x==fat[x]) return x;
		return getfat(fat[x]);
	}

	void join(int a, int b){
		a=getfat(a), b=getfat(b);
		if(sz[a]<sz[b]) swap(a, b);
		undoStack.push({a, b, fat[b], sz[a], nrComp});
		if(a==b) return;
		sz[a]+=sz[b];
		fat[b]=a;
		nrComp--;
	}
	
	void undo(){
		if(undoStack.empty()) return;
		auto data=undoStack.top();
		undoStack.pop();
		sz[data.a]=data.sza;
		fat[data.b]=data.fatb;
		nrComp=data.nrComp;
	}

	//Q part
	struct update{
		int type;
		int a, b;
	};
	vector<update> upds, aux[2];
	int nr1=0, bucketsize;
	void upd(int a, int b){
		upds.push_back({0, a, b});
		join(a, b);
	}

	void qUndo(){
		if(nr1==0){
			for(int i=0;i<upds.size();++i) undo();
			reverse(upds.begin(), upds.end());
			for(int i=0;i<upds.size();++i){
				join(upds[i].a, upds[i].b);
				upds[i].type=1;
			}
			nr1=upds.size();
			bucketsize=sqrt(nr1);
		}
		if(upds.back().type==0){
			while(upds.back().type==0){
				aux[0].push_back(upds.back());
				upds.pop_back();
				undo();
			}
			int sz=(nr1-1)%bucketsize+1;
			while(sz--){
				aux[1].push_back(upds.back());
				upds.pop_back();
				undo();
			}
			for(int type=0;type<2;++type){
				while(!aux[type].empty()){
					auto cr=aux[type].back();
					upds.push_back(cr);
					join(cr.a, cr.b);
					aux[type].pop_back();
				}
			}
		}
		assert(upds.back().type==1);
		nr1--;
		upds.pop_back();
		undo();
	}
};


int main(){
	int n, m;
	cin>>n>>m;
	vector<pair<int, int>> edges(m+1);
	for(int i=1;i<=m;++i){
		cin>>edges[i].first>>edges[i].second;
	}
	int p=0;
	DSUQ dsu(n);
	long long sol=0;

	for(int i=1;i<=m;++i){
		while(p<i||(dsu.nrComp>1&&p<=m)){
			p++;
			if(p==m+1) break;
			dsu.upd(edges[p].first, edges[p].second);
		}
		sol+=m-p+1;
		dsu.qUndo();
	}
	cout<<sol<<"\n";
}