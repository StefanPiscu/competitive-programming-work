#include <bits/stdc++.h>
using namespace std;


struct DSUWithQUndo{
	vector<int> fat;
	vector<int> sz;

	struct undoData{
		int type;
		int a, b;
		int sza, fatb;
	};
	vector<undoData> undoVec;
	int aCount;

	DSUWithQUndo(int n){
		fat.resize(n+1);
		sz.resize(n+1);
		for(int i=1;i<=n;++i){
			fat[i]=i;
			sz[i]=1;
		}
	}

	int getFat(int x){
		if(fat[x]==x) return x;
		return getFat(fat[x]);
	}

	void join(int a, int b, int type=0){
		int fa=getFat(a), fb=getFat(b);
		if(fa==fb){
			undoVec.push_back({type, fa, fb, -1, -1});
			return;
		}
		if(sz[fa]<sz[fb]) swap(fa, fb);
		undoData aux;
		undoVec.push_back({type, fa, fb, sz[fa], fat[fb]});
		sz[fa]+=sz[fb];
		fat[fb]=fa;
	}

	bool isConnected(int a, int b){
		if(getFat(a)==getFat(b)) return 1;
		return 0;
	}

	void undo(){
		undoData aux=undoVec.back();
		undoVec.pop_back();
		if(aux.sza==-1) return;
		fat[aux.b]=aux.fatb;
		sz[aux.a]=aux.sza;
	}

	void qUndo(){
		if(aCount==0){
			vector<pair<int, int>> joins;	
			while(!undoVec.empty()){
				joins.push_back({undoVec.back().a, undoVec.back().b});
				undo();
			}
			aCount=joins.size();
			for(auto elem:joins){
				join(elem.first, elem.second, 1);
			}
		}	
		if(undoVec.back().type==0){
			int nr=(aCount&(-aCount));
			stack<pair<int, int>> joins[2];
			while(nr){
				int type=undoVec.back().type;
				nr-=type;
				joins[type].push({undoVec.back().a, undoVec.back().b});
				undo();
			}
			for(int type:{0, 1}){
				while(!joins[type].empty()){
					int a, b;
					tie(a, b)=joins[type].top();
					joins[type].pop();
					join(a, b, type);
				}
			}
		}
		cout<<"Disconnecting "<<undoVec.back().a<<" "<<undoVec.back().b<<"\n";
		undo();
		aCount--;
	}
};

int main(){
	int n, m, q;
	cin>>n>>m>>q;
	DSUWithQUndo dsu(2*n+1);
	vector<pair<int, int>> edges(m+1);
	for(int i=1;i<=m;++i){
		cin>>edges[i].first>>edges[i].second;
	}
	vector<int> frst(m+1, m+1);
	int p=1;
	dsu.join(2*edges[p].first, 2*edges[p].second+1);
	cout<<"Connecting "<<2*edges[p].first<<" "<<2*edges[p].second+1<<"\n";
	dsu.join(2*edges[p].first+1, 2*edges[p].second);
	cout<<"Connecting "<<2*edges[p].first+1<<" "<<2*edges[p].second<<"\n";
	for(int i=1;i<=m;++i){
		while(!dsu.isConnected(2*edges[p].first, 2*edges[p].second)){
			p++;
			dsu.join(2*edges[p].first, 2*edges[p].second+1);
			cout<<"Connecting "<<2*edges[p].first<<" "<<2*edges[p].second+1<<"\n";
			dsu.join(2*edges[p].first+1, 2*edges[p].second);
			cout<<"Connecting "<<2*edges[p].first+1<<" "<<2*edges[p].second<<"\n";
		}
		frst[i]=p;
		//assert(p>i);
		dsu.qUndo();
		dsu.qUndo();
	}
	while(q--){
		int l, r;
		cin>>l>>r;
		if(r>=frst[l]) cout<<"YES\n";
		else cout<<"NO\n";
	}
	return 0;
}