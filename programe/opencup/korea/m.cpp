#include <bits/stdc++.h>
using namespace std;


int crn=0;

struct nodeX{
  int lazy;
  int leftson, rightson;
  int toY;
};

struct nodeY{
  int product;
  int lazy;
  int leftson, rightson;
};


vector<nodeX> vX;
vector<nodeY> vY;

void updateX(int x1, int y1, int x2, int y2, int crl, int crr, int pozx, int val){
  if(crl==x1&&crr==x2){
    updateY(y1, y2, vY[vX[pozx].toY], val);
  }

}

void updateY(int y1, int y2, int pozy, int val){
}

int main(){
  v.resize(4000000); 
}