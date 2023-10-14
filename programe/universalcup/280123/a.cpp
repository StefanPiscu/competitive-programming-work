#include <bits/stdc++.h>
using namespace std;

#define int long double

vector<int> numbers;
int N, M;
vector<pair<int, int>> A, B;

void prune(vector<pair<int, int>> &a){
	bool isReal=0;
	for(int i=0;i<a.size();++i){
		if(a[i].second>a[i].first) isReal=1;
	}	
	if(isReal){
		vector<pair<int, int>> a2;
		for(int i=0;i<a.size();++i) if(a[i].first<a[i].second) a2.push_back(a[i]);
		swap(a, a2);
	}
}

int32_t main(){
	cin>>N>>M;
	for(int i=1;i<=N;++i){
		pair<int, int> x;
		cin>>x.first>>x.second;
		numbers.push_back(x.first);
		numbers.push_back(x.second);
		A.push_back(x);
	}
	for(int i=1;i<=M;++i){
		pair<int, int> x;
		cin>>x.first>>x.second;
		numbers.push_back(x.first);
		numbers.push_back(x.second);
		B.push_back(x);
	}
	sort(numbers.begin(), numbers.end());
	numbers.resize(unique(numbers.begin(), numbers.end())-numbers.begin());
	sort(A.begin(), A.end());
	sort(B.begin(), B.end());

	vector<pair<int, int>> a, b;
	int p=0, nr=0, last=A[0].first;
	while(nr<numbers.size()&&p<A.size()){
		if(numbers[nr]<=A[p].first){
			nr++;
		}
		else if(A[p].second<=numbers[nr]){
			a.push_back({last, A[p].second});
			p++;
			last=A[p].first;
		}
		else{
			a.push_back({last, numbers[nr]});
			last=numbers[nr];
			nr++;
		}
	}
	while(p<A.size()) a.push_back({A[p].first, A[p].second}), p++;
	p=0, nr=0, last=B[0].first;
	while(nr<numbers.size()&&p<B.size()){
		if(numbers[nr]<=B[p].first){
			nr++;
		}
		else if(B[p].second<=numbers[nr]){
			b.push_back({last, B[p].second});
			p++;
			last=B[p].first;
		}
		else{
			b.push_back({last, numbers[nr]});
			last=numbers[nr];
			nr++;
		}
	}
	while(p<B.size()) b.push_back({B[p].first, B[p].second}), p++;

	prune(a);
	prune(b);


	long double lenA=0, lenB=0;
	for(int i=0;i<a.size();++i){
		if(a[i].second==a[i].first) lenA++;
		else lenA+=a[i].second-a[i].first;
	}
	for(int i=0;i<b.size();++i){
		if(b[i].second==b[i].first) lenB++;
		else lenB+=b[i].second-b[i].first;
	}

	int q=0;	
	long double sum1=0, sum2=0;
	long double ans=0;
	for(int p=0;p<a.size();++p){
		while(q<b.size()&&b[q].second<a[p].second){
			int prevs2=sum2;
			if(b[q].second==b[q].first) sum2++;
			else sum2+=b[q].second-b[q].first;
			sum1=(sum1*prevs2+(b[q].second+b[q].first)/2.0*(sum2-prevs2))/sum2;
			q++;
		}
		long double factA, factB;
		if(a[p].first==a[p].second) factA=1/lenA;
		else factA=(a[p].second-a[p].first)/lenA;
		if(b[q].first==a[p].first){
			if(b[q].first==b[q].second) factB=1/lenB;
			else factB=(b[q].second-b[q].first)/lenB;
			ans+=factA*factB*(a[p].second-a[p].first)/3.0;
		}
		factB=sum2/lenB;
		ans+=factA*factB*((a[p].second+a[p].first)/2.0-sum1);
	}
	q=b.size()-1;
	sum1=0, sum2=0;
	for(int p=a.size()-1;p>=0;--p){
		while(q>=0&&b[q].first>a[p].first){
			int prevs2=sum2;
			if(b[q].second==b[q].first) sum2++;
			else sum2+=b[q].second-b[q].first;
			sum1=(sum1*prevs2+(b[q].second+b[q].first)/2.0*(sum2-prevs2))/sum2;
			q--;
		}
		long double factA, factB;
		if(a[p].first==a[p].second) factA=1/lenA;
		else factA=(a[p].second-a[p].first)/lenA;
		factB=sum2/lenB;
		ans+=factA*factB*(sum1-(a[p].second+a[p].first)/2.0);
	}
	cout<<setprecision(12)<<fixed<<ans<<"\n";
	return 0;
}