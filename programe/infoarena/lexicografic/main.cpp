#pragma GCC optimize("O3")
#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("lexicografic.in");
ofstream fout("lexicografic.out");

#define mid (((l)+(r))/2)
#define ls (2*cr)
#define rs (2*cr+1)
struct segmentTree{
	int n;
	vector<int> val;
	vector<int> p;
	vector<int> nr;

	segmentTree(int _n){
		n=_n;
		val.resize((n+1)*4);
		p.resize((n+1)*4);
		nr.resize((n+1)*4);
	}

	void update(int poz, int x, int l, int r, int cr){
		if(l==r){
			val[cr]=x;
			p[cr]=l;
			nr[cr]=1;
			return;
		}
		if(poz<=mid) update(poz, x, l, mid, ls);
		else update(poz, x, mid+1, r, rs);
		nr[cr]=nr[ls]+nr[rs];
		if(val[ls]<=val[rs]) val[cr]=val[ls], p[cr]=p[ls];
		else val[cr]=val[rs], p[cr]=p[rs];
	}
	void update(int poz, int x){
		update(poz, x, 1, n, 1);
	}

	void del(int poz, int l, int r, int cr){
		if(l==r){
			nr[cr]=0, val[cr]=1e9, p[cr]=l;
			return;
		}
		if(poz<=mid) del(poz, l, mid, ls);
		else del(poz, mid+1, r, rs);
		nr[cr]=nr[ls]+nr[rs];
		if(val[ls]<=val[rs]) val[cr]=val[ls], p[cr]=p[ls];
		else val[cr]=val[rs], p[cr]=p[rs];
	}
	void del(int poz){
		del(poz, 1, n, 1);
	}

	pair<int, int> query(int k, int l, int r, int cr){
		//cerr<<k<<" "<<l<<" "<<r<<" "<<cr<<endl;
		if(k<=0) return {1e9, 0};
		if(k>=nr[cr]) return {val[cr], p[cr]};
		if(k>=nr[ls]) return min(query(nr[ls], l, mid, ls), query(k-nr[ls], mid+1, r, rs));
		return query(k, l, mid, ls);
	}
	pair<int, int> query(int k){
		return query(k, 1, n, 1);
	}

	int sumQuery(int x, int l, int r, int cr){
		if(x==r) return nr[cr];
		if(x<=mid) return sumQuery(x, l, mid, ls);
		else return sumQuery(mid, l, mid, ls)+sumQuery(x, mid+1, r, rs);
	}
	int sumQuery(int x){
		return sumQuery(x, 1, n, 1);
	}
};
#undef mid
#undef ls
#undef rs

void solve(){
	int n;
	long long k;
	cin>>n>>k;
	segmentTree aint(n);
	vector<int> v(n+1);
	for(int i=1;i<=n;++i){
		cin>>v[i];
		aint.update(i, v[i]);
	}
	int cr=1;
	for(int i=1;i<=n;++i){
		int mini, poz;
		//cerr<<k+1<<"\n";
		tie(mini, poz)=aint.query(k+1);
		//cerr<<mini<<" "<<poz<<"**"<<endl;
		cout<<mini<<" ";
		cout.flush();
		int val=aint.sumQuery(poz);
		k-=val-1;
		aint.del(poz);
	}
	cout<<"\n";
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}