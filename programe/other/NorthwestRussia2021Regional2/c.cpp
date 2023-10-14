#include <bits/stdc++.h>
using namespace std;

int n, k;
int sol;

struct trie{
	struct trieNod{
		int nrFiles=0;
		int sons[27]={0};
	};


	vector<trieNod> v;
	int getson(int x, char c){
		if(v[x].sons[c-'a']==0){
			int cr=v.size();
			v.push_back(trieNod());
			v[x].sons[c-'a']=cr;
			return cr;
		}
		else return v[x].sons[c-'a'];
	}

	trie(){
		v.push_back(trieNod());
	}

	void add(int cr, string &s, int ind){
		if(ind==s.size()){
			v[cr].nrFiles++;
			return;
		}
		int nx=getson(cr, s[ind]);
		add(nx, s, ind+1);
	}

	void add(string &s){
		add(0, s, 0);
	}

	int dfs(int x){
		int total=v[x].nrFiles;
		vector<int> vals;
		for(auto it:v[x].sons){
			if(it==0) continue;
			int nx=it;
			int val=dfs(nx);
			total+=val;
			vals.push_back(val);
		}
		sort(vals.begin(), vals.end(), greater<int>());
		int p=0;
		while(total>k){
			total-=vals[p];
			sol++;
			p++;	
		}
		return total;
	}

};

int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n>>k;
	trie myTrie;
	for(int i=1;i<=n;++i){
		string s;
		cin>>s;
		myTrie.add(s);
	}
	int x=myTrie.dfs(0);
	if(x!=0) sol++;
	cout<<sol<<"\n";
}