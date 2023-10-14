#include <bits/stdc++.h>
using namespace std;

#define MOD 1000000007

int t;

bool isPal(int nr){
	int ogl=0, aux=nr;
	while(aux){
		ogl=ogl*10+aux%10;
		aux/=10;
	}
	return ogl==nr;
}

int main(){
	vector<int> palnr;
	bitset<40002> isPalb;
	for(int i=1;i<=40000;++i){
		isPalb[i]=0;
		if(isPal(i)){
			isPalb[i]=1;
			palnr.push_back(i);
		}
	}
	vector<int> dp(40002);
	dp[0]=1;
	for(auto it:palnr){
		for(int i=it;i<=40000;++i){
			dp[i]+=dp[i-it];
			dp[i]%=MOD;
		}
	}
	cin>>t;
	while(t--){
		int n;
		cin>>n;
		cout<<dp[n]<<"\n";
	}
}