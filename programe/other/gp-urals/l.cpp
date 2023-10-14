#include <bits/stdc++.h>
using namespace std;


struct pig{
	int meat, fat, total;
	bool operator<(const pig &ot) const{
		return meat*(ot.fat+ot.meat)>ot.meat*(fat+meat);
	}
};

int n, k;


int32_t main(){
	cin>>n>>k;
	vector<pig> v(n+1);
	int maxTotal=0;
	for(int i=1;i<=n;++i) cin>>v[i].meat;
	for(int i=1;i<=n;++i) cin>>v[i].fat, v[i].total=v[i].fat+v[i].meat, maxTotal+=v[i].total;
	sort(v.begin()+1, v.end());
	vector<int> dp(maxTotal+1, 1e9);
	dp[0]=0;
	for(int i=1;i<=n;++i){
		for(int j=maxTotal;j>=v[i].total;--j) dp[j]=min(dp[j], dp[j-v[i].total]+v[i].fat);
	}
	//cout<<dp[100]<<" "<<dp[200]<<" "<<dp[300]<<"\n";
	if(maxTotal<k){
		cout<<"Reject\n";
		return 0;
	}
	int best=0;
	for(int j=k;j<=maxTotal;++j){
		int meat=j-dp[j], fat=dp[j];
	  if(meat*100ll>=(meat+fat)*70ll){
			cout<<"Outstanding\n";
			return 0;
		}
		else if(meat*100ll>=(meat+fat)*50ll) best=max(best, 1);
		else best=max(best, 0);
	}
	if(best==1) cout<<"Good Quality\n";
	else cout<<"Low Quality\n";
	return 0;
}