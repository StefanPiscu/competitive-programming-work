#include <bits/stdc++.h>
using namespace std;

int n, m;
bool a[302][302];

bool checkF(int x, int y){
	if(y+2>m) return 0;
	bool ret=a[x][y+1]&&a[x][y+2]&&a[x+2][y+1];
	if(ret){
		a[x][y+1]=0;
		a[x][y+2]=0;
		a[x+2][y+1]=0;
	}
	return ret;
}

bool checkQ(int x, int y){
	if(y<=2) return 0;
	bool ret=a[x][y-1]&&a[x][y-2]&&a[x+1][y-2]&&a[x+2][y-1]&&a[x+2][y-2];
	if(ret){
		a[x][y-1]=0;
		a[x][y-2]=0;
		a[x+1][y-2]=0;
		a[x+2][y-1]=0;
		a[x+2][y-2]=0;
	}
	return ret;
}

bool checkBar(int x, int y){
	bool bar=1;
	for(int k=0;k<5;++k) bar=bar&&a[x+k][y];
	return bar;
}

void deleteBar(int x, int y){
		for(int k=0;k<5;++k) a[x+k][y]=0;
}


int main(){
	cin>>n>>m;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			char x;
			cin>>x;
			if(x=='#') a[i][j]=1;
			else a[i][j]=0;
		}
	}
	int nrf=0, nrq=0;
	for(int j=1;j<=m;++j){
		for(int i=1;i<=n;++i){
			if(!a[i][j]) continue;
			bool bar=checkBar(i, j);
			if(bar&&checkF(i, j)){
				deleteBar(i, j);
				nrf++;
			}
			bar=checkBar(i, j+2);
			if(bar&&checkQ(i, j+2)){
				deleteBar(i, j+2);
				nrq++;
			}
		}
	}
	cout<<nrq<<" "<<nrf<<"\n";
}