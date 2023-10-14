#include <bits/stdc++.h>
using namespace std;


struct kube{
	int n;
	int coltop, colbot;
	struct corner{
		int t, b, l, r;
	};
	vector<corner> c;
	struct side{
		int t, b, s;
	};
	vector<side> s;

	kube(int _n){
		n=_n;
		c.resize(n+1);
		s.resize(n+1);
	}

	vector<int> solution;

	void twist(int i){
    i = (i - 1) % n + 1;
        solution.push_back(i);
        swap(s[i].t, s[i].b);
        int ca=i, cb=i%n+1;
        swap(c[ca].l, c[ca].r);
        swap(c[cb].l, c[cb].r);
        swap(c[ca].t, c[ca].b);
        swap(c[cb].t, c[cb].b);
        swap(c[ca], c[cb]);
  }

	void printSides(){
		for(int i=1;i<=n;++i){
			int ca=i, cb=i%n+1;
			cout<<c[ca].r<<" "<<s[i].s<<" "<<c[cb].l<<"\n";
		}
	}

	void printTop(){
		cout<<coltop<<"\n";
		for(int i=1;i<=n;++i){
			cout<<c[i].t<<" "<<s[i].t<<" ";
		}
		cout<<"\n";
	}

	bool checkTB(){
		for(int i=1;i<=n;++i){
			if(s[i].t!=coltop) return 0;
			if(c[i].t!=coltop) return 0;
			if(s[i].b!=colbot) return 0;
			if(c[i].b!=colbot) return 0;
		}
		return 1;
	}

	bool checkSides(){
		for(int i=1;i<=n;++i){
			int ca=i, cb=i%n+1;
			if(c[ca].r!=s[i].s) return 0;
			if(c[cb].l!=s[i].s) return 0;
		}
		return 1;
	}

	bool check(){
		return checkTB()&&checkSides();
	}

	void fixSides(){
		for(int j = 1; j <= n; j++){
			for(int i = 1; i <= n; i++){
				if(s[i].t != coltop){
						twist(i); twist(i + 1);
						twist(i); twist(i + 1);
						twist(i); twist(i + 1);
				}
			}
  	}
	}

	void fix2Corners(int i){
		for(int j=i-1;j!=(i-1)%n+1;j--){
			if(j<=0) j+=n;
			if(j==((i-1)%n+1)) break;
			twist(j);
		}
		for(int j=(i+1)%n+1;j!=(i-1)%n+1;j++){
			if(j>=n+1) j-=n;
			if(j==(i-1)%n+1) break;
			twist(j);
		}
		twist(i);
	}

	void fixAllCorners(){
		for(int i=1;i<=n;++i){
			if(c[i].t!=coltop){
				fix2Corners(i);
			}
		}
	}


	void solve(){
		int nr=2;

		vector<int> revCol(n+1);
		for(int i=1;i<=n;++i){
			revCol[s[i].s]=i;	
		}
		vector<int> poz(n+1);
		for(int i=1;i<=n;++i){
			int l=revCol[c[i].l], r=revCol[c[i].r];
			if(l>r) swap(l, r);
			if(r==l+1) poz[i]=l;
			else if(l==1&&r==n) poz[i]=0;
			else{
				cout<<-1<<"\n";
				return;
			}
		}
		cout<<"\n";
		for(int i=1;i<=n;++i){
			for(int j=1;j<n;++j){
				if(poz[j]>poz[j+1]){
					swap(poz[j], poz[j+1]);
					twist(j);
				}
			}
		}

		if(check()){
			cout<<solution.size()<<"\n";
			for(auto it:solution) cout<<it<<" ";
			cout<<"\n";
		}
		else{
			if(n%2) fixAllCorners();
			fixSides();
			if(check()){
				cout<<solution.size()<<"\n";
				for(auto it:solution) cout<<it<<" ";
				cout<<"\n";
			}
			else{
					cout<<-1<<"\n";
					return;
			}
		}
	}
};

int main(){
	srand(time(0));
	int n;
	cin>>n;
	kube myKube(n);
	cin>>myKube.coltop>>myKube.colbot;
	for(int i=1;i<=n;++i){
		cin>>myKube.c[i].t;
		cin>>myKube.c[i].l;
		cin>>myKube.c[i].r;
		cin>>myKube.c[i].b;
	}
	for(int i=1;i<=n;++i){
		cin>>myKube.s[i].t;
		cin>>myKube.s[i].s;
		cin>>myKube.s[i].b;
	}
	myKube.solve();
	return 0;
	int nrTests=10;
	while(nrTests--){
		kube copy=myKube;
		copy.solve();
	}
	return 0;
}