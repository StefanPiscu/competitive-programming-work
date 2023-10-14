#include <bits/stdc++.h>
using namespace std;

void solve(int n){
	if(n==4) cout<<1<<"\n";
	else if(n%2==0) cout<<n/2<<"\n";
	else cout<<n-3<<"\n";
}

/*
void solve(int n){
	if(n==4) cout<<1<<"\n";
	else{
		if(n%2==0) cout<<n/2<<"\n";
		else{
			for(int i=3;i<n;++i){
				if(n%i==0) cout<<n/i+solve(n/i);
			}
		}
	}
}
*/

int main(){
	int n;
	cin>>n;
	solve(n);
	return 0;
}
/*
(n-r)/c
4 = 1
5 = 2
8 = 4
*/