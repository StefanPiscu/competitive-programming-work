#include <bits/stdc++.h>
using namespace std;

#define _GLIBCXX_DEBUG
#define mid ((l+r)/2)
#define ls (2*cr)
#define rs (2*cr+1)
struct segmentTree{
	int n;
	vector<int> mini;
	vector<int> maxi;
	vector<int> lazy;
	
	segmentTree(int _n){
		n=_n+2;
		mini.resize(4*n+4);
		maxi.resize(4*n+4);
		lazy.resize(4*n+4);
	}
	void clean(int l, int r, int cr){
		if(lazy[cr]==0) return;
		mini[cr]+=lazy[cr];
		maxi[cr]+=lazy[cr];
		if(l<r){
			lazy[ls]+=lazy[cr];
			lazy[rs]+=lazy[cr];
		}
		lazy[cr]=0;
	}

	void update(int x, int ul, int ur, int l, int r, int cr){
		if(l==ul&&r==ur){
			lazy[cr]+=x;
			clean(l, r, cr);
			return;
		}	
		clean(l, mid, ls);
		clean(mid+1, r, rs);
		if(ur<=mid) update(x, ul, ur, l, mid, ls);
		else if(mid<ul) update(x, ul, ur, mid+1, r, rs);
		else{
			update(x, ul, mid, l, mid, ls);
			update(x, mid+1, ur, mid+1, r, rs);
		}
		clean(l, mid, ls);
		clean(mid+1, r, rs);
		mini[cr]=min(mini[ls], mini[rs]);
		maxi[cr]=max(maxi[ls], maxi[rs]);
	}
	void update(int x, int ul, int ur){
		update(x, ul, ur, 1, n, 1);
	}

	pair<int, int> query(int ql, int qr, int l, int r, int cr){
		if(ql==l&&qr==r){
			return {mini[cr], maxi[cr]};
		}
		clean(l, mid, ls);
		clean(mid+1, r, rs);
		if(qr<=mid) return query(ql, qr, l, mid, ls);
		if(mid<ql) return query(ql, qr, mid+1, r, rs);
		else{
			auto q1=query(ql, mid, l, mid, ls);
			auto q2=query(mid+1, qr, mid+1, r, rs);
			return {min(q1.first, q2.first), max(q1.second, q2.second)};
		}
	}
	pair<int, int> query(int ql, int qr){
		return query(ql, qr, 1, n, 1);
	}
};
#undef mid
#undef ls
#undef rs


int n, m;
int b, s;

struct ship{
	int id;
	int t, a, b, c;
};
vector<ship> ships;
struct bomb{
	int x1, y1, x2, y2;
};
vector<bomb> bombs;


struct rect{
	int x1, x2, l, r;
};
vector<rect> rects;
struct event{
	int id;
	int x, l, r;
	bool operator<(const event &ot) const{
		if(x==ot.x){
			int val=id, val2=ot.id;
			if(val==-1) val=1e9;
			if(val2==-1) val2=1e9;
			return val<val2;
		}
		return x<ot.x;
	}
};
vector<event> evs;
struct line{
	int id;
	int x, l, r;
};
vector<line> lines;

vector<int> ans;
void solve(int n){
	for(auto it:rects){
		//if(it.l>it.r) swap(it.l, it.r);
		evs.push_back({0, it.x1, it.l, it.r});
		evs.push_back({-1, it.x2, it.l, it.r});
	}
	for(auto it:lines){
		//if(it.l>it.r) swap(it.l, it.r);
		evs.push_back({it.id, it.x, it.l, it.r});
	}
	sort(evs.begin(), evs.end());

	segmentTree aint(n);
	for(auto it:evs){
		//cerr<<"EVENT: "<<it.id<<" "<<it.x<<" "<<it.l<<" "<<it.r<<"\n";
		if(it.id<=0){
			int val=0;
			if(it.id==0) val=1;
			else val=-1;
			aint.update(val, it.l, it.r);
		}
		else{
			auto resp=aint.query(it.l, it.r);
			if(resp.first==0){
				if(resp.second==0) ans[it.id]=0;
				else ans[it.id]=1;
			}
			else ans[it.id]=2;
		}
	}
}

int main(){
	cin>>n>>m;
	cin>>b;
	bombs.resize(b+1);
	for(int i=1;i<=b;++i){
		int a, b, c, d;
		cin>>a>>b>>c>>d;
		bombs[i]={a, b, c, d};
	}
	cin>>s;
	ships.resize(s+1);
	ans.resize(s+1);
	for(int i=1;i<=s;++i){
		int a, b, c, d;
		cin>>a>>b>>c>>d;
		ships[i]={i, a, b, c, d};
	}

	rects.clear();
	lines.clear();
	evs.clear();
	for(int i=1;i<=b;++i){
		//if(bombs[i].x1>bombs[i].x2) swap(bombs[i].x1, bombs[i].x2);
		//if(bombs[i].y1>bombs[i].y2) swap(bombs[i].y1, bombs[i].y2);
		rects.push_back({bombs[i].x1, bombs[i].x2, bombs[i].y1, bombs[i].y2});
	}
	for(int i=1;i<=s;++i){
		if(ships[i].t==1) lines.push_back({ships[i].id, ships[i].a, ships[i].b, ships[i].c});
	}
	solve(m);
	//cerr<<"-----------\n";

	rects.clear();
	lines.clear();
	evs.clear();	
	for(int i=1;i<=b;++i){
		rects.push_back({bombs[i].y1, bombs[i].y2, bombs[i].x1, bombs[i].x2});
	}
	for(int i=1;i<=s;++i){
		if(ships[i].t==2) lines.push_back({ships[i].id, ships[i].a, ships[i].b, ships[i].c});
	}
	solve(n);
	for(int i=1;i<=s;++i){
		if(ans[i]==0) cout<<"MISS\n";
		else if(ans[i]==1) cout<<"HIT\n";
		else cout<<"SUNK\n";
	}
	for(int i=1;i<=n;++i){
	}
}