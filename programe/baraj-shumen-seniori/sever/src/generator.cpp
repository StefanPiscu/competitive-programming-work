#include <bits/stdc++.h>
using namespace std;

struct FenwickTree{
  int n;
  vector<int> v;
  FenwickTree(int _n){
		n=_n+1;
    v.resize(n+1, 0);
  }
  void upd(int x, int val){
    for(;x<=n;x+=(x&-x)) v[x]+=val;
  }
  int qry(int x){
    int sol=0;
    for(;x;x-=(x&(-x))) sol+=v[x];
    return sol;
  }
	void clear(){
		v.clear();
		v.resize(n+1, 0);
	}
};

template <class T>
struct rmq{
  int lg(int x){
    return 31-__builtin_clz(x);
  }
  vector<vector<T>> mini;
  rmq(vector<T> v){
    mini.resize(v.size());
    for(int i=1;i<v.size();++i){
      mini[i].push_back(v[i]);
    }
    for(int pow=1;2*pow<v.size();pow*=2){
      for(int i=1;i+2*pow-1<v.size();++i){
        T val=min(mini[i].back(), mini[i+pow].back());
        mini[i].push_back(val);
      }
    }
  }
  T get(int l, int r){
    if(r<l) swap(l, r);
    int x=lg(r-l);
    return min(mini[l][x], mini[r-(1<<x)+1][x]);
  }
};

int n, m, q, isLant;
vector<pair<int, int>> edges;
vector<vector<int>> out;
vector<int> tin, tout, depth, firstPoz;
vector<int> cols, tols;
vector<pair<int, int>> euler;
vector<pair<int, int>> qrys;

vector<vector<int>> nodLists;
int crTime;
void dfs0(int x, int fat){
	tin[x]=++crTime;
	depth[x]=depth[fat]+1;
	firstPoz[x]=euler.size();
	int a=depth[x], b=euler.size();
	euler.push_back({depth[x], x});
	for(auto it:out[x]){
		if(it==fat) continue;
		dfs0(it, x);
	}
	tout[x]=++crTime;
	euler.push_back({depth[fat], fat});
}
rmq<pair<int, int>> ds({});
int lca(int a, int b){
	return ds.get(firstPoz[a], firstPoz[b]).second;
}

FenwickTree aib(0);
void addPath(int a, int b){
	int c=lca(a, b);
	aib.upd(tin[c], 1);
	aib.upd(tin[a]+1, -1);
	aib.upd(tin[c]+1, 1);
	aib.upd(tin[b]+1, -1);
}

int getCol(int c){
	int sol=0;
	for(auto nod:nodLists[c]){
		sol+=aib.qry(tin[nod]);
		sol-=aib.qry(tout[nod]);
	}
	return sol;
}
mt19937 getRandom;
vector<int> getColors(int n, int m){
	vector<int> ret(n+1);
	for(int i=1;i<=n;++i){
		ret[i]=getRandom()%m+1;
	}
	return ret;
}

int globalLen;
vector<pair<int, int>> getTree(int n){
	int lenLant=getRandom()%(n-1)+1;
	globalLen=lenLant;
	vector<pair<int, int>> edges;
	for(int i=1;i<lenLant;++i) edges.push_back({i, i+1});
	for(int i=lenLant+1;i<=n;++i) edges.push_back({getRandom()%(i-1)+1, i});
	vector<int> eye(n+1);
	for(int i=1;i<=n;++i) eye[i]=i;
	std::random_shuffle(eye.begin()+1, eye.end());
	vector<pair<int, int>> edges2;
	for(auto it:edges){
		int a=eye[it.first], b=eye[it.second];
		if(a>b) swap(a, b);
		edges2.push_back({a, b});
	}
	return edges2;
}

vector<pair<int, int>> getLant(int n){
	vector<pair<int, int>> ret;
	for(int i=1;i<n;++i) ret.push_back({i, i+1});
	return ret;
}

pair<int, int> getQuery(int n){
	int u, v;
	do{
		u=getRandom()%n+1, v=getRandom()%n+1;
	}while(u==v);
	if(v>u) swap(v, u);
	return {v, u};
}

vector<pair<int, int>> getQueries(int q, int n){
	vector<pair<int, int>> queries(q+1);
	for(int i=1;i<=q;++i) queries[i]=getQuery(n);
	return queries;
}

int getRandBetween(int a, int b){
	uniform_int_distribution<> distrib(a, b);
	return distrib(getRandom);
}

void init(int n){
	out.resize(n+1);
	tin.resize(n+1);
	tout.resize(n+1);
	depth.resize(n+1);
	firstPoz.resize(n+1);
}



int main(){
	int seed;
	cin>>seed;
	srand(seed);
	getRandom=mt19937(seed);
	cin>>n>>m>>q;
	edges=getTree(n);	
	cols=getColors(n, m);
	qrys=getQueries(q, n);

	cerr<<globalLen<<"*\n";

	init(n);
	for(auto it:edges) out[it.first].push_back(it.second), out[it.second].push_back(it.first);
	euler.push_back({0, 0});
	dfs0(1, 0);
	ds=rmq<pair<int, int>>(euler);
	nodLists.resize(m+1);
	for(int i=1;i<=n;++i){
		nodLists[cols[i]].push_back(i);
	}
	aib=FenwickTree(crTime);
	vector<int> shuffledCols;
	vector<int> pozCol;
	for(int i=1;i<=m;++i) shuffledCols.push_back(i);
	std::random_shuffle(shuffledCols.begin(), shuffledCols.end());
	vector<pair<int, int>> elem;
	for(int i=0;i<m;++i){
		int crCol=shuffledCols[i];
		int val=getRandBetween(1LL*q*i/m, 1LL*q*(i+1)/m)+1;
		elem.push_back({val, crCol});
		cerr.flush();
	}
	std::sort(elem.begin(), elem.end());
	int cr=0;
	tols.resize(m+1);
	for(int i=1;i<=q;++i){
		addPath(qrys[i].first, qrys[i].second);
		while(cr<elem.size()&&i==elem[cr].first){
			tols[elem[cr].second]=max(0, getCol(elem[cr].second)-1);
			cr++;
		}
	}
	cout<<n<<" "<<m<<"\n";
	for(auto it:edges) std::cout<<it.first<<" "<<it.second<<"\n";
	for(int i=1;i<=n;++i) std::cout<<cols[i]<<" ";
	std::cout<<"\n";
	for(int i=1;i<=m;++i) std::cout<<tols[i]<<" ";
	std::cout<<"\n";
	std::cout<<q<<"\n";
	for(int i=1;i<=q;++i) std::cout<<qrys[i].first<<" "<<qrys[i].second<<"\n";
}
