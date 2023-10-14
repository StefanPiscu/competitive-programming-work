#include <bits/stdc++.h>
using namespace std;

#define int long long

int n;
unordered_map<int, int> cols;
multiset<int, greater<int>> values;

struct elem{
	int x, y;
	int val;
};

bool cmpx(elem a, elem b){
	return a.x<b.x;
}

vector<elem> v;

int32_t main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	cin>>n;
	v.resize(n+1);
	for(int i=1;i<=n;++i){
		cin>>v[i].x>>v[i].y>>v[i].val;
		cols[v[i].y]+=v[i].val;
	}
	//
	sort(v.begin(), v.end(), cmpx);
	for(auto it:cols){
		values.insert(it.second);
	}
	int best=0;
	int nr=3, sum=0;
	for(auto it=values.begin();it!=values.end()&&nr;it++,nr--){
		sum+=(*it);
	}
	//cout<<sum<<"*\n";
	best=max(best, sum);
	for(int i=1;i<=n;){
		int x=v[i].x;
		int j=i;
		int sum=0;
		while(v[j].x==x&&j<v.size()){
			int val=cols[v[j].y];
			cols[v[j].y]-=v[j].val;
			values.erase(values.find(val));
			values.insert(val-v[j].val);
			sum+=v[j].val;
			j++;
		}
		int nr=2; 
		for(auto it=values.begin();it!=values.end()&&nr;it++,nr--){
			sum+=(*it);
		}
		//cout<<sum<<" "<<x<<"\n";
		best=max(best, sum);
		while(v[i].x==x&&i<v.size()){
			int val=cols[v[i].y];
			cols[v[i].y]+=v[i].val;
			values.erase(values.find(val));
			values.insert(val+v[i].val);
			i++;
		}
	}
	cols.clear();
	values.clear();
	for(int i=1;i<=n;++i){
		swap(v[i].x, v[i].y);
		cols[v[i].y]+=v[i].val;
	}
	sort(v.begin(), v.end(), cmpx);
	for(auto it:cols){
		values.insert(it.second);
	}
	best=0;
	nr=3, sum=0;
	for(auto it=values.begin();it!=values.end()&&nr;it++,nr--){
		sum+=(*it);
	}
	//cout<<sum<<"**\n";
	best=max(best, sum);
	for(int i=1;i<=n;){
		int x=v[i].x;
		int j=i;
		int sum=0;
		while(v[j].x==x&&j<v.size()){
			int val=cols[v[j].y];
			cols[v[j].y]-=v[j].val;
			values.erase(values.find(val));
			values.insert(val-v[j].val);
			sum+=v[j].val;
			j++;
		}
		int nr=2;
		for(auto it=values.begin();it!=values.end()&&nr;it++,nr--){
			sum+=(*it);
		}
		best=max(best, sum);
		//cout<<sum<<" "<<x<<"*\n";
		while(v[i].x==x&&i<v.size()){
			int val=cols[v[i].y];
			cols[v[i].y]+=v[i].val;
			values.erase(values.find(val));
			values.insert(val+v[i].val);
			i++;
		}
	}
	cout<<best<<"\n";
}

