#include <bits/stdc++.h>
using namespace std;
 
struct edge{
	int u, v, id;
	int weight;
};
 
int n, m, k;
vector<int> parent, sz; // представники та розміри множин у системі неперетинних множин
vector<edge> edges;
 
int find(int x) { // знаходимо представника вершини
	return parent[x] = (parent[x] == x ? x : find(parent[x]));
}
 
bool unite(int x, int y) { // пробуємо додати ребро в каркас
	x = find(x);
	y = find(y);
	if (x == y) return false;
 
	if (sz[x] < sz[y]) swap(x, y);
	sz[x] += sz[y];
	parent[y] = x;
	return true;
}
 
vector<int> mst(vector<edge>& G){
	for(int i = 1; i <= n; ++i){
		parent[i] = i;
		sz[i] = 1;
	}
		
	sort(G.begin(), G.end(), [&](edge l, edge r){
		return l.weight < r.weight || (l.weight==r.weight&&0);
	});
	
	vector<int> mst;
	for(edge e: G){
		if (unite(e.u, e.v)){
			mst.push_back(e.id);
		}
	}
	
	return mst;
}
 
vector<int> find_mst(int x){
	vector<edge> G = edges;
	for(edge& e: G){
		if (e.u == 1 || e.v == 1) e.weight += x;
	}
	
	return mst(G);
}
 
int H(vector<int> mst){
	int cnt = 0;
	for(int id: mst){
		if (edges[id].u == 1 || edges[id].v == 1){
			cnt++;
		}
	}
	return cnt;
}
 
int main(){
	cin >> n >> m >> k;
	edges.resize(m);
	parent.resize(n + 1);
	sz.resize(n + 1);
	
	for(int i = 0; i < m; ++i){
		edge& e = edges[i];
		e.id = i;
		cin >> e.u >> e.v >> e.weight;	
		e.weight *= 2;
	}
	
	int l = INT_MIN / 2, r = INT_MAX / 2;
	for(int it = 0; it < 100; ++it){
		int x = (l + r) >> 1;
		int h = H(find_mst(x));
		if (h >= k) l = x;
		else r = x;
	}
  cout<<l<<"***\n";
  cout<<H(find_mst(-7))<<" "<<H(find_mst(-6))<<" "<<H(find_mst(-5))<<"\n";
	vector<int> ans = find_mst(l);
	if (H(ans) != k){
		cout << -1 << endl;
	}else{
		cout << n - 1 << endl;
		for(int i: ans){
			cout << edges[i].id + 1 << ' ';
		}
		cout << endl;
	}
	
	return 0;
}