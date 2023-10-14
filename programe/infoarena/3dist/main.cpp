#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream fin("3dist.in");
ofstream fout("3dist.out");

int n;

struct point{
	int x, y;
	int yNorm;
	int d;

	bool operator<(const point &other) const{
		return x<other.x||(x==other.x&&y<other.y);
	}

};
map<pair<int, int>, int> mp;
int yNormMax;
vector<point> v;

struct normalizer{
private:
	unordered_map<int, int> toNormal;
	vector<int> fromNormal;
	

public:
	normalizer(vector<int> data){
		sort(data.begin(), data.end());
		data.resize(unique(data.begin(), data.end())-data.begin());
		fromNormal.resize(data.size()+1);
		for(int i=0;i<data.size();++i){
			toNormal[data[i]]=i+1;
			fromNormal[i+1]=data[i];
		}	
	}

	int normalize(int x){
		return toNormal[x];
	}

	int getValue(int x){
		return fromNormal[x];
	}
};

#define mid ((l+r)/2)
#define ls (2*cr)
#define rs (2*cr+1)
struct segmentTree{
	int n;
	vector<int> val;
	segmentTree(int _n){
		n=_n+1;
		val.resize(4*n+1, 2e9);
	}

	void update(int poz, int x, int l, int r, int cr){
		if(l==r){
			val[cr]=min(val[cr], x);
			return;
		}
		if(poz<=mid) update(poz, x, l, mid, ls);
		else update(poz, x, mid+1, r, rs);
		val[cr]=min(val[ls], val[rs]);
	}
	void update(int poz, int x){
		update(poz, x, 1, n, 1);
	}

	int query(int ql, int qr, int l, int r, int cr){
		cerr<<ql<<" "<<qr<<" "<<l<<" "<<r<<" "<<cr<<endl;
		assert(ql!=0);
		if(ql==l&&qr==r) return val[cr];
		if(qr<=mid) return query(ql, qr, l, mid, ls);
		if(mid<ql) return query(ql, qr, mid+1, r, rs);
		return min(query(ql, mid, l, mid, ls), query(mid+1, qr, mid+1, r, rs));
	}
	int query(int ql, int qr){
		return query(ql, qr, 1, n, 1);
	}

};
#undef mid
#undef ls
#undef rs

void solveLeftToRight(){
	segmentTree aintPlusY(yNormMax), aintMinusY(yNormMax);
	for(int i=1;i<=n;++i){
		auto &it=v[i];
		int valuePlusY, valueMinusY;
		cerr<<it.y<<" "<<it.yNorm<<"*"<<endl;
		valuePlusY=aintPlusY.query(it.yNorm, yNormMax);
		valueMinusY=aintMinusY.query(1, it.yNorm);
		int value=it.x+min(valuePlusY-it.y, it.y+valueMinusY);
		it.d=min(it.d, value);
		aintPlusY.update(it.yNorm, -it.x+it.y);
		aintMinusY.update(it.yNorm, -it.x-it.y);
	}
}

void solveRightToLeft(){
	segmentTree aintPlusY(yNormMax), aintMinusY(yNormMax);
	reverse(v.begin()+1, v.end());
	for(int i=1;i<=n;++i){
		auto &it=v[i];
		int valuePlusY, valueMinusY;
		cerr<<it.y<<" "<<it.yNorm<<"*"<<endl;
		valuePlusY=aintPlusY.query(it.yNorm, yNormMax);
		valueMinusY=aintMinusY.query(1, it.yNorm);
		int value=-it.x+min(valuePlusY-it.y, it.y+valueMinusY);
		it.d=min(it.d, value);
		aintPlusY.update(it.yNorm, it.x+it.y);
		aintMinusY.update(it.yNorm, it.x-it.y);
	}
	reverse(v.begin()+1, v.end());
}

bool compareByD(point a, point b){
	return a.d<b.d;
}
vector<point> currentPoints;

bool compareByMainDiag(point a, point b){
	if(a.x+a.y==b.x+b.y) return a<b;
	return a.x+a.y<b.x+b.y;
}
void solveMainDiagonals();


bool compareBySecondaryDiag(point a, point b){
	if(a.x-a.y==b.x-b.y) return a<b;
	return a.x-a.y<b.x-b.y;
}
void solveSecondaryDiagonals();

int main(){
	cin>>n;
	v.resize(n+1);
	vector<int> yValues;
	for(int i=1;i<=n;++i){
		cin>>v[i].x>>v[i].y;
		v[i].d=2e9;
		yValues.push_back(v[i].y);
	}
	normalizer normer(yValues);
	sort(v.begin()+1, v.end());
	for(int i=1;i<=n;++i){
		v[i].yNorm=normer.normalize(v[i].y);
		yNormMax=max(v[i].yNorm, yNormMax);
	}
	solveLeftToRight();
	solveRightToLeft();
	for(int i=1;i<=n;++i){
		mp[make_pair(v[i].x, v[i].y)]=v[i].d;
	}
	sort(v.begin()+1, v.end(), compareByD);
}