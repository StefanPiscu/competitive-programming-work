#include <bits/stdc++.h>
using namespace std;


struct point{
	int x, y;

	const point operator-(const point &b) const{
		return {x-b.x, y-b.y};
	}
};

struct vec{
	point org;
	int x, y;
};

int sgn(int x){
	if(x>0) return 1;
	if(x==0) return 0;
	return -1;
}

int cross(vec v, point p){
	p=p-v.org;
	return v.x*p.y-v.y*p.x;
}

struct segment{
	point a, b;
};

bool intersectVS(vec a, segment b){
	int c1=sgn(cross(a, b.a)), c2=sgn(cross(a, b.b));
	if(c1==0&&c2==0) return 0;
	if(c1*c2<0) return 1;
	return 0;
}

bool intersectVV(vec a, vec b){
	int sumX=a.org.x+b.org.x;
	int sumY=a.org.x+b.org.y;
	int val=sumX*a.y-sumY*a.org.x;	
	
}



point start, end;
vector<segment> s;
vector<pair<int, int>> startVecs, endVecs;


int main(){
}