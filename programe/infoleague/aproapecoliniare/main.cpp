#include <bits/stdc++.h>
using namespace std;

int n;

struct point{
	int first, second;
	int orig;
}

vector<point> pct;

bool cmp1(point a, point b){
	if(a.first==b.first) return a.second<b.second;
}
bool cmp2(point a, point b){
	if(a.first==b.first) return a.second>b.second;
}

struct FenwickTree{
	int n;
	vector<int> aib;
	FenwickTree(int _n){
		n=_n+1;
		aib.resize(n+2);
	}
	void upd(int poz, int x){
		for(poz++;poz<=n;poz+=(poz&-poz)) aib[poz]+=x;
	}
	int qry(int poz){
		int sum=0;
		for(poz++;poz;poz-=(poz&-poz)) sum+=aib[poz];
		return sum;
	}
};

int main(){
	cin>>n;
	pct.resize(n+1);
	for(int i=1;i<=n;++i) cin>>pct[i].first>>pct[i].second, pct[i].orig=i;
	sort(pct.begin(), pct.end(), cmp1);
	vector<int> cnt1, cnt2;
	int counter=0;
	FenwickTree aib(n);
	for(int i=1;i<=n;++i){
		cnt1[pct[i].orig]=aib.qry(pct[i].second);
		cnt2[pct[i].orig]=counter-aib.qry(pct[i].second);
		aib.upd(pct[i].second, 1);
		counter++;
	}
	FenwickTree aib2(n);
	return 0;
}