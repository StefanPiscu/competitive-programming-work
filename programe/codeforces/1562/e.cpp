#include <iostream>
using namespace std;

int main(){
	int n, s, nr;
	cin>>n>>s;

	for(int i=1;i<10000000;++i){
		int aux=i;
		int sum=0, nrc=0;
		while(aux){
			int uc=aux%10;
			sum=sum+uc;
			aux=aux/10;
			nrc++;
		}
		if(nrc==n&&sum==s){
			cout<<i<<" ";
			nr++;
		}
	} 
	cout<<"\n";
	cout<<nr<<"\n";
	return 0;
}