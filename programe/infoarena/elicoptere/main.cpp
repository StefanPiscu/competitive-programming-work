#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream fin("elicoptere.in");
ofstream fout("elicoptere.out");

struct point{
	double x, y;
};

struct triangle{
	point t[3];
};


point vIntersect(double x, point a, point b){
	if(a.x>b.x) swap(a, b);
	if(b.y==a.y) return {x, b.y};
	double y=((x-a.x)/(b.x-a.x))*(b.y-a.y)+a.y;
	return {x, y};
}

point hIntersect(double y, point a, point b){
	if(b.x==a.x) return {b.x, y};
	double x=((y-a.y)/(b.y-a.y))*(b.x-a.x)+a.x;
	return {x, y};
}

double getMinDist(point a, point a1, point b1){
	double sol=1e9;
	//cout<<a.x<<" "<<a.y<<"\n";
	//cout<<a1.x<<" "<<a1.y<<" "<<b1.x<<" "<<b1.y<<"\n";
	if(a1.x==b1.x&&a1.x==a.x){
		sol=min({sol, abs(a.y-a1.y), abs(a.y-b1.y)});
	}
	else if(min(a1.x, b1.x)<=a.x&&a.x<=max(a1.x, b1.x)){
		point pa=vIntersect(a.x, a1, b1);
		sol=min(sol, abs(pa.y-a.y));
	}
	if(a1.y==b1.y&&a1.y==a.y){
		sol=min({sol, abs(a.x-a1.x), abs(a.x-b1.x)});
	}
	else if(min(a1.y, b1.y)<=a.y&&a.y<=max(a1.y, b1.y)){
		point pa=hIntersect(a.y, a1, b1);
		//cout<<pa.x<<" "<<pa.y<<"*\n";
		sol=min(sol, abs(pa.x-a.x));
	}
	//cout<<sol<<"\n";
	return sol;
}

double getMinDist(point a1, point b1, point a2, point b2){
	return min({getMinDist(a1, a2, b2), getMinDist(b1, a2, b2), getMinDist(a2, a1, b1), getMinDist(b2, a1, b1)});
}

double getMinDist(triangle a, triangle b){
	double dist=1e9;
	for(int i=0;i<3;++i){
		for(int j=0;j<3;++j){
			dist=min(dist, getMinDist(a.t[i], a.t[(i+1)%3], b.t[j], b.t[(j+1)%3]));
		}
	}
	return dist;
}

struct edge{
	int a, b;
	double c;
	bool operator<(const edge &ot) const{
		return c<ot.c;
	}
};

vector<int> fat;
vector<int> sz;
double sol=0;
int nr=0;

int get(int x){
	if(x==fat[x]) return x;
	return fat[x]=get(fat[x]);
}

void join(int a, int b, double c){
	a=get(a), b=get(b);
	if(a==b) return;
	nr++;
	sol+=c;
	if(sz[a]<sz[b]) swap(a, b);
	sz[a]+=sz[b];
	fat[b]=a;
}

int main(){
	int cer;
	cin>>cer;
	int n;
	double k;
	cin>>n>>k;
	vector<triangle> v(n+1);
	for(int i=1;i<=n;++i){
		for(int j=0;j<3;++j){
			cin>>v[i].t[j].x>>v[i].t[j].y;
		}
	}
	vector<edge> edges;
	for(int i=1;i<=n;++i){
		for(int j=i+1;j<=n;++j){
			double dist=getMinDist(v[i], v[j]);
			if(dist<=k) edges.push_back({i, j, dist});
		}
	}
	sort(edges.begin(), edges.end());
	fat.resize(n+1);
	sz.resize(n+1);
	for(int i=1;i<=n;++i) fat[i]=i, sz[i]=1;
	for(auto it:edges){
		join(it.a, it.b, it.c);
	}
	if(cer==1) cout<<nr<<"\n";
	else if(cer==3) cout<<fixed<<setprecision(5)<<sol<<"\n";
	else{
		vector<bool> used(n+1);
		int ans=0;
		for(int i=1;i<=n;++i){
			int x=get(i);
			if(!used[x]){
				used[x]=1;
				ans+=sz[x]*(sz[x]-1)/2;
			}
		}
		cout<<ans<<"\n";
	}
	return 0;
}