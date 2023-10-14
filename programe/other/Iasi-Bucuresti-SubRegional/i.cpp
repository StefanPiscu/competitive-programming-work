#include <bits/stdc++.h>
using namespace std;

#define int long long
#define MOD 1000000007

int binpow(int b, int e){
	int sol=1;
	while(e){
		if(e&1) sol=sol*b%MOD;
		b=b*b%MOD;
		e>>=1;
	}
	return sol;
}

void brutforce(string s){
	int nrq=0;
	for(auto it:s) if(it=='?') nrq++;
	int sol=0;
	for(int i=0;i<(1<<nrq);++i){
		string t=s;
		int bit=0;
		int nr1=0, nr0=0;
		//cout<<t<<"\n";
		for(auto &it:t){
			if(it=='?'){
				if(i&(1<<bit)) it='1';
				else it='0';
				bit++;
			}
			if(it=='0') sol+=nr1, nr0++;
			else nr1++;
		}
		//cout<<t<<"*\n";
		//cout<<"*\n";
	}
	cout<<sol<<"\n";	
}


int32_t main(){
	string s;
	cin>>s;
	int nr1=0, nrq=0;
	int sol=0;
	for(int i=0;i<s.size();++i){
		if(s[i]=='1') nr1++;
		else if(s[i]=='?'){
			int aux=sol;
			sol+=((nr1*binpow(2, nrq))%MOD);
			if(nrq) sol+=((binpow(2, (nrq-1))*nrq)%MOD);
			sol%=MOD;
			sol+=aux;
			nrq++;
		}
		else{
			sol+=((nr1*binpow(2, nrq))%MOD);
			if(nrq) sol+=((binpow(2, (nrq-1))*nrq)%MOD);
			sol%=MOD;
		}
		//cout<<i<<" "<<sol<<"\n";
	}
	//brutforce(s);
	cout<<sol%MOD<<"\n";
	return 0;
}