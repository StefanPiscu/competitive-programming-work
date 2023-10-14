#include <bits/stdc++.h>
using namespace std;

ifstream fin("cerc3.in");
ofstream fout("cerc3.out");

int n;
unordered_map<long double, vector<pair<long double, long double>>> drepte;

int main(){
	fin>>n;
	for(int i=1;i<=n;++i){
		int x, y, r;
		fin>>x>>y>>r;
		long double d=sqrt(1LL*x*x+1LL*y*y);
		long double panta=(long double)x/(long double)y;
		drepte[panta].push_back({d+r, d-r});
	}
	fout<<drepte.size()<<" ";
	int nrMax=0, nrNrMax=0;
	for(auto it:drepte){
		auto &intervals=it.second;
		sort(intervals.begin(), intervals.end());
		int nr=0;
		long double last=0;
		for(auto it:intervals){
			long double l, r;
			tie(r, l)=it;
			if(l>last){
				nr++;
				last=r;
			}
		}
		if(nr==nrMax) nrNrMax++;
		else if(nr>nrMax) nrMax=nr, nrNrMax=1;
	}
	fout<<nrMax<<" "<<nrNrMax<<"\n";
}