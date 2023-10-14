#include <bits/stdc++.h>
using namespace std;
#include <stdio.h>
#include <ctype.h>

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}
	
	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
	
	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};
#define cin fin
#define cout fout
ifstream fin("sever.in");
ofstream fout("sever.out");

struct FenwickTree{
  int n;
  vector<int> v;
  FenwickTree(int _n){
		n=_n+1;
    v.resize(n+1, 0);
  }
  void upd(int x, int val){
    for(;x<=n;x+=(x&(-x))) v[x]+=val;
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

vector<vector<int>> out;
vector<int> tin, tout, depth, firstPoz;
vector<int> tols,  cols;
vector<pair<int,int>> qrys;
vector<pair<int, int>> euler;

vector<vector<int>> nodLists;
struct srcData{
	int col, l, r, sol;
	const bool operator<(const srcData &ot) const{
		return (l+r)<(ot.l+ot.r);
	}
};

int crTime;
void dfs0(int x, int fat){
	tin[x]=++crTime;
	depth[x]=depth[fat]+1;
	firstPoz[x]=euler.size();
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

void init(int n){
	out.resize(n+1);
	tin.resize(n+1);
	tout.resize(n+1);
	depth.resize(n+1);
	firstPoz.resize(n+1);
}

int main(){
	int n, m;
	cin>>n>>m;
	init(n);
	for(int i=1;i<n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	cols.resize(n+1);
	for(int i=1;i<=n;++i) cin>>cols[i];
	tols.resize(m+1);
	for(int i=1;i<=m;++i) cin>>tols[i];
	int q;
	cin>>q;
	qrys.resize(q+1);
	for(int i=1;i<=q;++i){
		cin>>qrys[i].first>>qrys[i].second;
	}
	euler.push_back({0, 0});
	dfs0(1, 0);
	ds=rmq<pair<int, int>>(euler);

	nodLists.resize(m+1);
	for(int i=1;i<=n;++i){
		nodLists[cols[i]].push_back(i);
	}
	aib=FenwickTree(crTime);
	vector<srcData> elem;	
	for(int i=1;i<=m;++i){
		elem.push_back({i, 1, q, -1});
	}
	bool changed=1;
	while(changed){
		changed=0;
		aib.clear();
		sort(elem.begin(), elem.end());
		int cr=0;
		while(cr<elem.size()&&elem[cr].l>elem[cr].r) cr++;
		for(int i=1;i<=q;++i){
			addPath(qrys[i].first, qrys[i].second);
			while(cr<elem.size()&&(elem[cr].l+elem[cr].r)/2==i){
				changed=1;
				int mid=(elem[cr].l+elem[cr].r)/2;
				if(getCol(elem[cr].col)>tols[elem[cr].col]){
					elem[cr].sol=mid;
					elem[cr].r=mid-1;
				}
				else{
					elem[cr].l=mid+1;
				}
				do cr++;
				while(cr<elem.size()&&elem[cr].l>elem[cr].r);
			}
		}
	}
	vector<int> sol(m+1);
	for(auto it:elem) sol[it.col]=it.sol;
	for(int i=1;i<=m;++i) cout<<sol[i]<<" ";
	cout<<"\n";
	return 0;
}
