#include <bits/stdc++.h>
using namespace std;

#define int long long


template<typename NodeType=char>
struct SuffixAutomaton{

	struct state{
		int len, link;
		map<NodeType, int> next;
		int isClone=0;
		vector<int> rlinks;
		int count, firstpos;
	};
	vector<state> st;
	int last=0;
	int nr=0;

	SuffixAutomaton(){
		st.push_back({0, -1});
		st[0].count=0;
		st[0].firstpos=-1;
		last=0;
	}

	int getTransition(int p, NodeType x){
		int q=st[p].next[x];
		if(st[q].len==st[p].len+1) return q;
		int clone=st.size();
		st.push_back({st[p].len+1, st[q].link, st[q].next, q});
		st[clone].firstpos=st[q].firstpos;
		while(p!=-1&&st[p].next[x]==q){
			st[p].next[x]=clone;
			p=st[p].link;
		}
		st[q].link=clone;
		return clone;
	}

	void addNode(NodeType x){
		int p=last;
		if(st[last].next.count(x)){
			last=getTransition(p, x);
			return;
		}
		int cr=st.size();
		st.push_back({st[p].len+1, 0});
		st[cr].firstpos=st[cr].len-1;
		while(p!=-1&&!st[p].next.count(x)){
			st[p].next[x]=cr;
			p=st[p].link;
		}
		if(p==-1){
			st[cr].link=0;
		}
		else{
			int val=getTransition(p, x);
			st[cr].link=val;
		}
		nr+=st[cr].len-st[st[cr].link].len;
		last=cr;
	}

	int endString(){
		int ret=last;
		last=0;
		return ret;
	}

};

int32_t main(){
	int n;
	cin>>n;
	string s;
	cin>>s;
	vector<vector<int>> lev(n+1);
	int crl=0;
	SuffixAutomaton<int> mySA;
	for(int i=0;i<n;++i){
		if(s[i]=='(') crl++;
		else{
			for(auto it:lev[crl]) mySA.addNode(it);
			int val=mySA.endString();
			lev[crl].clear();
			if(crl>0){
				crl--;
				lev[crl].push_back(val);
			}
		}
	}
	while(crl>=0){
		for(auto it:lev[crl]) mySA.addNode(it);
		lev[crl].clear();
		mySA.endString();
		crl--;
	}
	cout<<mySA.nr<<"\n";
}

