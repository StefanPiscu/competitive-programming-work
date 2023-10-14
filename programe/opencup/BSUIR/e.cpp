#include <bits/stdc++.h>
using namespace std;

int n, m;

struct state{
	int cx, cy;
	int dx, dy;
};
char a[64][64];

int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};

bool moveCat(state &crState, int dir){
	state newState=crState;
	newState.cx+=dx[dir];
	newState.cy+=dy[dir];
	if(newState.cx<=0||n<newState.cx||newState.cy<=0||m<newState.cy||a[newState.cx][newState.cy])
}

state moveDog(state crState){
}

int main(){
}