#include <bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
ifstream cin("immortal.in");
ofstream cout("immortal.out");

#define convert(i, j) (((i)*m)+(j))

int n, m;
vector<int> rev;
bitset<400> state;
vector<pair<pair<int, int>, pair<int, int>>> solution;

void jump(int i1, int j1, int i2, int j2, int i3, int j3);

void bk(){
	if(state.count()==1){
		for(auto it:solution){
			cout<<it.first.first+1<<" "<<it.first.second+1<<" "<<it.second.first+1<<" "<<it.second.second+1<<"\n";
		}
		exit(0);
	}
	for(int poz=0;poz<n*m;poz++){
		int i=poz/m, j=poz%m;
		jump(i, j, i+1, j, i+2, j);
		jump(i, j, i-1, j, i-2, j);
		jump(i, j, i, j+1, i, j+2);
		jump(i, j, i, j-1, i, j-2);
	}
}

void jump(int a, int k){
	int i1, i2, i3, j1, j2, j3;
	if(i3<0||n<=i3||j3<0||m<=j3||!state[convert(i1, j1)]||!state[convert(i2, j2)]||state[convert(i3, j3)]) return;
	state.flip(convert(i1, j1));
	state.flip(convert(i2, j2));
	state.flip(convert(i3, j3));
	solution.push_back({{i1, j1}, {i3, j3}});
	bk();
	solution.pop_back();
	state.flip(convert(i1, j1));
	state.flip(convert(i2, j2));
	state.flip(convert(i3, j3));
}

int main(){
	int k;
	cin>>n>>m>>k;
	for(int i=1;i<=k;++i){
		int a, b;
		cin>>a>>b;
		state[convert(a-1, b-1)]=1;
	}
	bk();
	assert(0);
	return 0;
}