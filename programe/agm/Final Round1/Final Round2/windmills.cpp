#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
using namespace std;

#define MOD 998244353

struct matrix{
	int rows, cols;
	vector<vector<int>> a;

	matrix(int _rows, int _cols){
		rows=_rows, cols=_cols;
		a.resize(rows+1, vector<int>(cols+1, 0));
	}

	matrix operator*(const matrix &ot) const{
		matrix c(rows, ot.cols);
		for(int i=1;i<=rows;++i){
			for(int k=1;k<=cols;++k){
				if(a[i][k]==0) continue;
				for(int j=1;j<=ot.cols;++j){
					c.a[i][j]=(c.a[i][j]+(1LL*a[i][k]*ot.a[k][j])%MOD)%MOD;
				}
			}
		}
		return c;
	}
};

void 

int main(){
	
	return 0;
}