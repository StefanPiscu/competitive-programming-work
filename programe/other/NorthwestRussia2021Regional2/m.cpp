#include <bits/stdc++.h>
using namespace std;

int t;

struct assignment{
	string s;
	int val;
};

unordered_map<string, bool> used;
unordered_map<string, int> vals;

vector<stack<assignment>> v;


int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>t;
	v.resize(t);
	for(int i=0;i<t;++i){
		int n;
		cin>>n;
		while(n--){
			string s;
			cin>>s;
			int x=s.find('=');
			string varName=s.substr(0, x);
			string number=s.substr(x+1, s.size());
			stringstream ss;
			ss<<number;
			int val;
			ss>>val;
			v[i].push({varName, val});
		}
	}
	int nrval;
	cin>>nrval;
	for(int i=1;i<=nrval;++i){
		string s;
		int val;
		cin>>s>>val;
		vals[s]=val;
	}
	bool done=0;
	int nrset=0;
	stack<int> sol;
	while(!done){
		done=1;
		for(int i=0;i<t;++i){
			if(v[i].empty()) continue;
			auto x=v[i].top();
			if(used[x.s]){
				sol.push(i);
				v[i].pop();
				done=0;
			}
			else if(x.val==vals[x.s]){
				used[x.s]=true;
				sol.push(i);
				nrset++;
				v[i].pop();
				done=0;
			}
		}
	}
	if(nrset==nrval){
		cout<<"Yes\n";
		while(!sol.empty()){
			cout<<sol.top()+1<<" ";
			sol.pop();
		}
	}
	else cout<<"No\n";
	return 0;
}