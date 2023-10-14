#include <bits/stdc++.h>
using namespace std;

int main(){
	int a, b, c, d, e, f;
	cin>>a>>b>>c>>d>>e>>f;
	int p1=b*d*f, p2=a*c*e;
	if(p1!=p2){
		cout<<-1<<"\n";
		return 0;
	}
	long double ab=100000;
	long double ac=ab*e/f, bc=ab*b/a;
	long double maxi=max({ab, ac, bc});
	if(maxi>=ab+ac+bc-maxi){
		cout<<-1<<"\n";
	}
	else cout<<1<<"\n";
}