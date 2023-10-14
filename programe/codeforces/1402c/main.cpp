#include <bits/stdc++.h>
using namespace std;

/*
  Solution
  Define some variables for each node;
  nrL = the number of nodes that are Losing states if reached
  define a critical node if attaching a losing node to it would cause it to swap the root
  notice that attaching it to a winning node does nothing
  nrC = the number of critical nodes for this root
  nrL and nrC are calcullable with dfs-topdown-dp
  ok so if the tree has no additional dimension it's clear we can just output the number of winning nodes
  now if we add another dimension of it happens to be from a critical node it may change the result of the game, if we attach it to a losing root
  let's define a swapping setup the number of ways to set up portals so that your first entrance, the one that goes from your root tree is losing
  let L[1] be the number of swapping setups in a 1 dimensional graph, this is obviously the number of losing nodes
  we can imagine adding some swapping setup, under a current swapping setup 


  

*/

struct nod{
  int nrLn=0; //number of Losing neighbours
  int nrL=0; //number of losing nodes in subtree
  int nrC=0;
  vector<int> out;
};

vector<nod> g;

void dfsL(int x, int fat){
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfsL(it, x);
    if(g[it].nrLn>0) g[x].nrLn++;
    g[x].nrL+=g[it].nrL;
  }
  if(g[x].nrLn==0) g[x].nrL++;
}

void dfsC(int x, int fat){
 bool type=(bool)g[x].nrLn;
  for(auto it:g[x].out){
    if(it==fat) continue;
    dfsC(it, x);
    if(g[it].nrLn==0&&g[x].nrLn==1) g[x].nrC+=g[it].nrC;
    else if(g[it].nrLn>0&&g[x].nrLn==0) g[x].nrC+=g[it].nrC;
  }
  if(g[x].nrLn==0) g[x].nrC++;
}

int getdp(int d){

}

int main(){

}