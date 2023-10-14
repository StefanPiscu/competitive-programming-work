#include <bits/stdc++.h>
using namespace std;
#include <stdio.h>
#include <ctype.h>

class InParser {
private:
	FILE *fin;
	char *buff;
	int sp;

	char read_ch() {
		++sp;
		if (sp == 4096) {
			sp = 0;
			fread(buff, 1, 4096, fin);
		}
		return buff[sp];
	}

public:
	InParser(const char* nume) {
		fin = fopen(nume, "r");
		buff = new char[4096]();
		sp = 4095;
	}
	
	InParser& operator >> (int &n) {
		char c;
		while (!isdigit(c = read_ch()) && c != '-');
		int sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
	
	InParser& operator >> (long long &n) {
		char c;
		n = 0;
		while (!isdigit(c = read_ch()) && c != '-');
		long long sgn = 1;
		if (c == '-') {
			n = 0;
			sgn = -1;
		} else {
			n = c - '0';
		}
		while (isdigit(c = read_ch())) {
			n = 10 * n + c - '0';
		}
		n *= sgn;
		return *this;
	}
};
#define cin fin
#define cout fout
ifstream fin("sever.in");
ofstream fout("sever.out");

vector<int> fat;
vector<vector<int>> out;
vector<int> tin, tout;
vector<int> tols, contor, cols;

int crTime;
void dfs0(int x, int par){
	tin[x]=crTime++;
	fat[x]=par;
	for(auto it:out[x]){
		if(it==par) continue;
		dfs0(it, x);
	}
	tout[x]=crTime++;
}

inline bool isanc(int a, int b){
	return tin[a]<=tin[b]&&tout[b]<=tout[a];
}

queue<int> broken;
void addPath(int a, int b){
	while(!isanc(a, b)){
		contor[cols[a]]++;
		if(contor[cols[a]]==tols[cols[a]]+1) broken.push(cols[a]);
		a=fat[a];
	}
	while(b!=a){
		contor[cols[b]]++;
		if(contor[cols[b]]==tols[cols[b]]+1) broken.push(cols[b]);
		b=fat[b];
	}
	contor[cols[a]]++;
	if(contor[cols[a]]==tols[cols[a]]+1) broken.push(cols[a]);
}

int main(){
	int n, m;
	cin>>n>>m;
	out.resize(n+1);
	fat.resize(n+1);
	tin.resize(n+1);
	tout.resize(n+1);
	for(int i=2;i<=n;++i){
		int a, b;
		cin>>a>>b;
		out[a].push_back(b);
		out[b].push_back(a);
	}
	dfs0(1, 0);
	cols.resize(n+1);
	for(int i=1;i<=n;++i) cin>>cols[i];
	tols.resize(m+1);
	for(int i=1;i<=m;++i) cin>>tols[i];
	contor.resize(m+1);
	int q;
	cin>>q;
	vector<int> sol(m+1, -1);
	for(int t=1;t<=q;++t){
		int a, b;
		cin>>a>>b;
		addPath(a, b);
		while(!broken.empty()){
			int cr=broken.front();
			broken.pop();
			sol[cr]=t;
		}
	}
	for(int i=1;i<=m;++i) cout<<sol[i]<<" ";
	cout<<"\n";
	return 0;
}

/*
9 4
1 2 3 4 1 6 7 8
3 3 3 1 1 2 2 2 4
2 4 6 0
5
3 5
1 3
1 9
3 4
2 7

Sol:
4 5 5 3
*/
