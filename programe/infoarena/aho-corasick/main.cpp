#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout

ifstream cin("ahocorasick.in");
ofstream cout("ahocorasick.out");

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
		last=cr;
	}


	void computeCount(int x=0){
		for(auto it:st[x].rlinks){
			computeCount(it);
			st[x].count+=st[it].count;
		}
	}

	void compute(){
		for(int i=1;i<st.size();++i){
			st[st[i].link].rlinks.push_back(i);
			st[i].count=!st[i].isClone;
		}
		computeCount();
	}

	int getCount(string s){
		int cr=0;
		for(auto it:s){
			if(st[cr].next.count(it)==0) return 0;
			cr=st[cr].next[it];
		}
		return st[cr].count;
	}

};

int main(){
	string s;
	cin>>s;
	SuffixAutomaton<char> SA;
	for(auto it:s) SA.addNode(it);
	SA.compute();
	int n;
	cin>>n;
	while(n--){
		string t;
		cin>>t;
		cout<<SA.getCount(t)<<"\n";
	}
};