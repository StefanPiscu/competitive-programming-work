#include <bits/stdc++.h>
using namespace std;

#define int long long

struct fibForm{
	int nrx, nry;
	const fibForm operator+(const fibForm& ot){
		return {nrx+ot.nrx, nry+ot.nry};
	}
};



int32_t main(){
	int n;
	cin>>n;
	int nr=2;
	vector<fibForm> fib;
	fib.push_back({1, 0});
	fib.push_back({0, 1});
	while(min(fib.back().nrx, fib.back().nry)<=n){
		fib.push_back(fib[nr-1]+fib[nr-2]);
		nr++;
	}
	int bestx=0, besty=n;
	for(int i=2;i<nr;++i){
		for(int x=0;x*fib[i].nrx<=n;++x){
			int dif=n-fib[i].nrx*x;
			if(dif%fib[i].nry) continue;
			int y=dif/fib[i].nry;
			if((x+y)<(bestx+besty)||((x+y)==(bestx+besty)&&x<bestx)){
				bestx=x, besty=y;
			}
		}
	}
	cout<<bestx<<" "<<besty<<"\n";
	return 0;
}