#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <bits/stdc++.h>

using ll = long long;

void sleep(int time){

}


int const nmax = 5000;
int v[5 + nmax], ch[5 + nmax][2], far[5 + nmax], vRev[5 + nmax];
int seen[5 + nmax], depth[5 + nmax];
std::vector<std::pair<int,int>> sol;

void set(int node, int side, int to) {
  assert(side != -1);

  ch[node][side] = to;
  far[to] = node;
}

int side(int node) {
  if(node == 0 || far[node] == 0)
    return -1;
  int parent = far[node];
  if(ch[parent][0] == node)
    return 0;
  else if(ch[parent][1] == node)
    return 1;
  return -1;
}

void computeDepth(int node) {
  depth[node] = std::max(depth[ch[node][0]], depth[ch[node][1]]) + 1;
}

void bruh(bool cond, float slep) {
  if(!cond) {
    int xored = 0;
    clock_t start = clock();

    while((1. * clock() - start) / CLOCKS_PER_SEC) < slep) {
      int x = rand();
      xored ^= x;
    }

    exit(-1);
  }
}

void rotate(int node) {
  if(node == 0 || far[node] == 0)
    return ;
  int parent = far[node];
  int sd = side(node);
  int parent2 = far[parent];
  int sd2 = side(parent);

  set(parent, sd, ch[node][!sd]);
  set(node, !sd, parent);
  computeDepth(parent);
  computeDepth(node);

  if(parent2 != 0) {
    set(parent2, sd2, node);
    computeDepth(parent2);
  } else
    far[node] = 0;

  sol.push_back({0, node});
}

void dfs(int node) {
  if(ch[node][0] != 0)
    dfs(ch[node][0]);
  if(ch[node][1] != 0)
    dfs(ch[node][1]);
  computeDepth(node);
}

void buildBamboo(int node) {
  if(0 < ch[node][0] && 0 < ch[node][1]) {
    if(depth[ch[node][0]] < depth[ch[node][1]]) {
      buildBamboo(ch[node][1]);
      int root = node;
      while(0 < ch[node][0]) {
        int newRoot = ch[node][0];
        rotate(newRoot);
        root = newRoot;
      }
    } else {
      buildBamboo(ch[node][0]);
      int root = node;
      while(0 < ch[node][1]) {
        int newRoot = ch[node][1];
        rotate(newRoot);
        root = newRoot;
      }
    }
  }
}

void recoverBamboo(int node, std::vector<int> &bamboo) {
  if(node == 0)
    return ;

  recoverBamboo(ch[node][0], bamboo);
  bamboo.push_back(node); 
  recoverBamboo(ch[node][1], bamboo);
}

void normalize(int n) {
  std::vector<int> aux;
  for(int i = 1;i <= n; i++)
    aux.push_back(v[i]);
  std::sort(aux.begin(), aux.end());
  aux.erase(std::unique(aux.begin(), aux.end()), aux.end());
  for(int i = 1; i <= n; i++)
    v[i] = std::lower_bound(aux.begin(), aux.end(), v[i]) - aux.begin() + 1;
}

void balanceBamboo(std::vector<int> &bamboo) {
  for(int i = 0; i < bamboo.size(); i++)
    for(int h = 0; h < __builtin_ctz(i + 1); h++)
      rotate(bamboo[i]);
}

std::vector<std::pair<int,int>> toSwap;

void repair(int val, std::vector<int> &bamboo) {
  int from = vRev[val];
  int to = bamboo[val - 1];
  if(from == to)
    return ;
  toSwap.push_back({from, to});
  std::swap(v[from], v[to]);
  std::swap(vRev[v[from]], vRev[v[to]]);
  repair(v[from], bamboo);
  return ;
}

int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int n;
  std::cin >> n;
  for(int i = 1;i <= n; i++) {
    std::cin >> v[i] >> ch[i][0] >> ch[i][1]; 
    if(ch[i][0] != 0)
      far[ch[i][0]] = i;
    if(ch[i][1] != 0)
      far[ch[i][1]] = i;
  }
  
  int root;
  for(int i = 1; i <= n; i++)
    if(far[i] == 0)
      root = i;

  dfs(root);
  std::vector<int> bamboo;
  buildBamboo(root);
  for(int i = 1; i <= n; i++)
    if(far[i] == 0)
      root = i;
  
  recoverBamboo(root, bamboo);
 
  if(far[bamboo[0]] != 0) {
    for(int h = bamboo.size() - 2; 0 <= h; h--)
      rotate(bamboo[h]);
    root = bamboo[0];

    bamboo.clear();
    recoverBamboo(root, bamboo);
  }

  /*
  std::cout << "Bamboo\n"; 
  for(int i = 1; i <= n; i++)
    std::cout << far[i] << " " << ch[i][0] << " " << ch[i][1] << '\n';
  for(int i = 0; i < bamboo.size(); i++)
    std::cout << bamboo[i] << " ";
  std::cout << '\n';
  */

  balanceBamboo(bamboo);
  normalize(n);
  
  for(int i = 1;i <= n; i++)
    vRev[v[i]] = i;
   
  for(int i = 1;i <= n; i++)
    repair(i, bamboo);
  
  for(int i = 0; i < toSwap.size(); i++) {
    int x = toSwap[i].first;
    int y = toSwap[i].second;
    std::vector<int> path1;
    while(far[x] != 0) {
      path1.push_back(far[x]);
      rotate(x);
    }
    std::vector<int> path2;
    while(far[y] != 0) {
      path2.push_back(far[y]);
      rotate(y);
    }
    sol.push_back({1, x});
    
    for(int h = path2.size() - 1; 0 <= h; h--)
      rotate(path2[h]);
    for(int h = path1.size() - 1; 0 <= h; h--)
      rotate(path1[h]);
  }

	assert(toSwap
  assert(sol.size()<=300000);
  std::cout << sol.size() << '\n';

  for(int i = 0; i < sol.size(); i++)
    if(sol[i].first == 0)
      std::cout << "rotate " << sol[i].second << '\n';
    else
      std::cout << "swap " << sol[i].second << '\n';
  return 0;
}
