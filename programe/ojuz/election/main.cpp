#include <bits/stdc++.h>
using namespace std;

#define int long long

#define mid ((l+r)/2)
#define ls (2*cr)
#define rs (2*cr+1)
struct segmentTree{
	struct data{
		int pref, suf, sum, sol;
	};
	data join(data a, data b){
		data ret;
		ret.pref=max(a.pref, a.sum+b.pref);
		ret.suf=max(a.suf+b.sum, b.suf);
		ret.sum=a.sum+b.sum;
		ret.sol=max({a.pref+b.suf, a.sol+b.sum, a.sum+b.sol});
		return ret;
	}
	int n;
	vector<data> v;

	segmentTree(int _n){
		n=_n;
		v.resize(4*n+2);
	}

	void build(string &val, int l, int r, int cr){
		if(l==r){
			if(val[l]=='C') v[cr].pref=0, v[cr].suf=0, v[cr].sol=0, v[cr].sum=-1;
			else v[cr].pref=1, v[cr].suf=1, v[cr].sol=1, v[cr].sum=1;
		}
		else{
			build(val, l, mid, ls);
			build(val, mid+1, r, rs);
			v[cr]=join(v[ls], v[rs]);
		}
	}
	void build(string &val){
		build(val, 1, n, 1);
	}
	

	data query(int ql, int qr, int l, int r, int cr){
		if(ql==l&&qr==r){
			return v[cr];
		}
		else{
			if(qr<=mid) return query(ql, qr, l, mid, ls);
			if(mid<ql) return query(ql, qr, mid+1, r, rs);
			return join(query(ql, mid, l, mid, ls), query(mid+1, qr, mid+1, r, rs));
		}
	}

	int query(int l, int r){
		return query(l, r, 1, n, 1).sol;
	}
};
#undef mid 
#undef ls
#undef rs


int32_t main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	s='$'+s;
	segmentTree aint=segmentTree(n);
	aint.build(s);
	int q;
	cin>>q;
	while(q--){
		int l, r;
		cin>>l>>r;
		cout<<aint.query(l, r)<<"\n";
	}
	return 0;
}