#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<pair<int, int>>> events;
vector<pair<int, int>> maxi1, maxi2;
vector<vector<int>> rrec;


struct restriction{
	int l, r;
	int h;
};
vector<restriction> rec;

struct LazySegmentTree {
    const static int offset = (1 << 19);
    struct node {
        int minim = 1e9, lazy = 0;
    } aint[2 * offset];

    void push_lazy(int node) {
        aint[node].minim += aint[node].lazy;
        if(node < offset) {
            aint[2 * node].lazy += aint[node].lazy;
            aint[2 * node + 1].lazy += aint[node].lazy;
        }
        aint[node].lazy = 0;
    }

    void rebuild(int node) {
        aint[node].minim = min(aint[2 * node].minim, aint[2 * node + 1].minim);
    }

    void _update(int node, int l, int r, int gl, int gr, int val) {
        push_lazy(node);
        if(r < gl || gr < l) return;
        if(gl <= l && r <= gr) {
            aint[node].lazy += val;
            push_lazy(node);
            return;
        }

        int mid = (l + r) / 2;
        _update(2 * node, l, mid, gl, gr, val);
        _update(2 * node+1, mid + 1, r, gl, gr, val);
        rebuild(node);
    }

    int _query(int node, int l, int r, int gl, int gr) {
        push_lazy(node);
        if(r < gl || gr < l) return 1e9;
        if(gl <= l && r <= gr) return aint[node].minim;

        int mid = (l + r) / 2;
        int a = _query(2 * node, l, mid, gl, gr);
        int b = _query(2 * node + 1, mid + 1, r, gl, gr);

        return min(a, b);
    }

    void set_value(int poz, int value) {
        int cnt = _query(1, 0, offset - 1, poz, poz);
        _update(1, 0, offset - 1, poz, poz, value - cnt);
    }

    void update(int l, int r, int val) {
				//cout<<l<<" "<<r<<" "<<val<<"\n";
        _update(1, 0, offset - 1, l, r, val);
    }

    int query(int l, int r) {
        return _query(1, 0, offset - 1, l, r);
    }
};

LazySegmentTree aint;

int main(){
	cin>>n>>m; 
	events.resize(n+2);
	maxi1.resize(n+3);
	maxi2.resize(n+3);
	rec.resize(m+3);
	rrec.resize(m+3);
	for(int i=1;i<=m;++i){
		cin>>rec[i].h>>rec[i].l>>rec[i].r;
		events[rec[i].l].push_back({rec[i].h, i});
		events[rec[i].r+1].push_back({rec[i].h, -i});
	}	
	events[1].push_back({0, m+1});
	events[1].push_back({0, m+2});
	set<pair<int, int>> elems;
	for(int i=1;i<=n;++i){
		for(auto it:events[i]){
			if(it.second>=0){
				elems.insert({-it.first, it.second});
			}
			else{
				elems.erase({-it.first, -it.second});
			}
		}
		auto it=elems.begin();
		maxi1[i]=(*it);
		maxi1[i].first*=-1;
		rrec[maxi1[i].second].push_back(i);
		maxi2[i]=(*next(it)); 
		maxi2[i].first*=-1;
		/*
		cout<<i<<"\n";
		cout<<maxi1[i].first<<" "<<maxi1[i].second<<"\n";
		cout<<maxi2[i].first<<" "<<maxi2[i].second<<"\n";
		cout<<"\n";
		*/
	}
	for(int i=1;i<=n;++i){
		aint.set_value(i, n-i+1);
		//cout<<i<<" "<<n-i+1<<"\n";
	}
	//cout<<"\n";
	for(int i=1;i<=n;++i){
		aint.update(1, maxi1[i].first, -1);
		//cout<<maxi1[i].first<<" "<<n<<" "<<-1<<"\n";
	}
	for(int i=1;i<=m;++i){
		for(auto it:rrec[i]){
			aint.update(1, maxi1[it].first, 1);
			aint.update(1, maxi2[it].first, -1);
		}
		if(aint.query(1, n)>=0){
			cout<<"YES\n";
			for(auto it:rrec[i]){
				maxi1[it]=maxi2[it];
			}
			vector<pair<int, int>> idk;
			for(int i=1;i<=n;++i){
				idk.push_back({maxi1[i].first, i});
			}
			sort(idk.begin(), idk.end());
			vector<int> sol(n+1);
			int nr=1;
			for(auto it:idk){
				sol[it.second]=nr++;
			}
			for(int i=1;i<=n;++i) cout<<sol[i]<<" ";
			cout<<"\n";
			return 0;
		}
		for(auto it:rrec[i]){
			aint.update(1, maxi1[it].first, -1);
			aint.update(1, maxi2[it].first, +1);
		}
	}
	cout<<"NO\n";
}