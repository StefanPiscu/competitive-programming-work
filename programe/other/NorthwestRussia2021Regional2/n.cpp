#include <bits/stdc++.h>
using namespace std;


int n;
int nrw, nrb;
vector<int> outw, outb;
vector<int> w, b;

void solve(){
	cin>>n;
	w.clear();
	w.resize(n+1);
	b.clear();
	b.resize(n+1);
	nrw=0, nrb=0;
	outw.clear(), outb.clear();
	int sum=0;
	for(int i=1;i<=n;++i){
		cin>>w[i]>>b[i];
		sum+=w[i];
		sum+=b[i];
		for(int j=1;j<=w[i];++j) outw.push_back(i);
		for(int j=1;j<=b[i];++j) outb.push_back(i);
	}
	if(sum!=(n-1)*2){
		cout<<"No\n";
		return;
	}
	stack<int> st;
	vector<int> euler;
	st.push(1);
	while(!st.empty()){
		int x=st.top();
		if(x==n+1){
			if(nrw==outw.size()){
				euler.push_back(x);
				st.pop();
			}
			else{
				st.push(outw[nrw]);
				nrw++;
			}
		}
		else if(x==n+2){
			if(nrb==outb.size()){
				euler.push_back(x);
				st.pop();
			}
			else{
				st.push(outb[nrb]);
				nrb++;
			}
		}
		else{
			if(w[x]){
				st.push(n+1);
				w[x]--;
			}
			else if(b[x]){
				st.push(n+2);
				b[x]--;
			}
			else{
				euler.push_back(x);
				st.pop();
			}
		}
	}
	cout<<"Yes\n";
	for(auto it:euler){
		if(it==n+1) cout<<"W ";
		else if(it==n+2) cout<<"B ";
		else cout<<it<<" ";
	}
	cout<<"\n";
}

int main(){
	int t;
	cin>>t;
	while(t--){
		solve();
	}
}