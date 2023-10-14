#include <bits/stdc++.h>
using namespace std;

int n;
long double val;

int main(){
	cin>>n;
	for(int i=2;i<=n;++i){
		val+=(2.0)/((long double)i);
	}
	long double sol=0;
	for(int i=1;i<=n;++i){
		long double x;
		cin>>x;
		sol+=x*val;
	}
	cout<<fixed<<setprecision(10)<<sol<<"\n";
}