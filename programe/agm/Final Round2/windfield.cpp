#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define int long long
#define MOD 998244353

int binpow(int b, int e){
	int sol=1;
	while(e){
		if(e&1) sol=1LL*sol*b%MOD;
		b=1LL*b*b%MOD;
		e>>=1;
	}
	return sol;
}

int n;

int convert(int i, int j){
	return (i-1)*n+j-1;
}

struct matrix{
	int rows, cols;
	vector<vector<int>> a;

	matrix(int _rows=0, int _cols=0){
		rows=_rows, cols=_cols;
		a.resize(rows, vector<int>(cols, 0));
	}

	matrix operator*(const matrix &ot) const{
		matrix c(rows, ot.cols);
		for(int i=0;i<rows;++i){
			for(int j=0;j<ot.cols;++j){
				//if(a[i][k]==0) continue;
				for(int k=0;k<cols;++k){
					c.a[i][j]=(c.a[i][j]+(1LL*a[i][k]*ot.a[k][j])%MOD)%MOD;
				}
			}
		}
		return c;
	}
};

struct elem{
	int same, up, righ, down, lef;
};

elem a[502][502];
int l=0, ol=1;
long long probs[502][502][2];
int sump, sumi;

void simulate(){
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			if(i-1) probs[i-1][j][ol]+=probs[i][j][l]*a[i][j].up;
			if(j-1) probs[i][j-1][ol]+=probs[i][j][l]*a[i][j].lef;
			if(i+1<=n) probs[i+1][j][ol]+=probs[i][j][l]*a[i][j].down;
			if(j+1<=n) probs[i][j+1][ol]+=probs[i][j][l]*a[i][j].righ;
			probs[i][j][ol]+=probs[i][j][l]*a[i][j].same;
		}
	}
	l=1-l;
	ol=1-l;
	sump=0, sumi=0;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			probs[i][j][l]%=MOD;
			if(j%2) sumi+=probs[i][j][l];
			else sump+=probs[i][j][l];
			sumi%=MOD;
			sump%=MOD;
			probs[i][j][ol]=0;
		}
	}
}



int32_t main(){
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>a[i][j].same;
			if(i-1) cin>>a[i][j].up;
			if(j<n) cin>>a[i][j].righ;
			if(i<n) cin>>a[i][j].down;
			if(j-1) cin>>a[i][j].lef;
		}
	}
	int idk=binpow(n*n, MOD-2);
	//cout<<idk<<"*\n";
	/*
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cout<<probs[i][j][l]<<" ";
		}
		cout<<"\n";
	}
	*/
	int q;
	cin>>q;
	vector<int> qrys(q+1);
	int maxK=0;
	for(int i=1;i<=q;++i) cin>>qrys[i], maxK=max(maxK, qrys[i]);
	if(n>10){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				probs[i][j][l]=idk;
			}
		}
		vector<int> sols(maxK+2);
		for(int k=1;k<=maxK;++k){
			simulate();
			/*
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					cout<<probs[i][j][l]<<" ";
				}
				cout<<"\n";
			}
			*/
			if(k%2) sols[k]=sump;
			else sols[k]=sumi;
		}
		for(int i=1;i<=q;++i){
			cout<<sols[qrys[i]]<<"\n";
		}
	}
	else{
		matrix transition(n*n, n*n);
		matrix init(n*n, 1);
		for(int i=0;i<n*n;++i){
			init.a[i][0]=idk;
		}
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i<n) transition.a[convert(i+1, j)][convert(i, j)]=a[i][j].down;
				if(i-1) transition.a[convert(i-1, j)][convert(i, j)]=a[i][j].up;
				if(j<n) transition.a[convert(i, j+1)][convert(i, j)]=a[i][j].righ;
				if(j-1) transition.a[convert(i, j-1)][convert(i, j)]=a[i][j].lef;
				transition.a[convert(i, j)][convert(i, j)]=a[i][j].same;
			}
		}
		vector<matrix> pow(33);
		pow[1]=transition;
		for(int i=2;i<=32;++i) pow[i]=pow[i-1]*pow[i-1];
		for(int i=1;i<=q;++i){
			sump=0, sumi=0;
			int k=qrys[i];
			matrix aux=init;
			//while(k--) aux=transition*aux;
			///*
			for(int bit=0;bit<32;++bit){
				if(k&(1<<bit)) aux=pow[bit+1]*aux;
			}
			//*/
			
			for(int i=1;i<=n;++i){
				for(int j=1;j<=n;++j){
					//cout<<aux.a[convert(i, j)][0]<<" ";
					if(j%2==0) sump+=aux.a[convert(i, j)][0], sump%=MOD;
					else sumi+=aux.a[convert(i, j)][0], sumi%=MOD;
				}
				//cout<<"\n";
			}
			if(k%2) cout<<sump<<"\n";
			else cout<<sumi<<"\n";
		}
	}
	return 0;
}