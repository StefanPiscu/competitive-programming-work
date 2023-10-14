#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cassert>

using ll = long long;

int const nmax = 200000;

std::vector<std::vector<int>> g;
std::vector<int> low_link, init;
std::vector<int> in_stack;
std::vector<int> st, level;
int n;
void SCC(int n_) {
  n = n_;
  g.resize(1 + n);
  low_link.resize(1 + n);
  init.resize(1 + n);
  in_stack.resize(1 + n);
  level.resize(1 + n);
}

void add_edge(int x, int y) {
  g[x].push_back(y);
}

int curr = 0;

void dfs(int node, int &ptr) {
  init[node] = low_link[node] = ptr++;
  in_stack[node] = 1;
  st.push_back(node);

  for(int h = 0;h < g[node].size(); h++) {
    int to = g[node][h];
    if(low_link[to] == 0) {
      dfs(to, ptr);
      low_link[node] = std::min(low_link[node], low_link[to]);
    } else if(in_stack[to] == 1) 
      low_link[node] = std::min(low_link[node], low_link[to]);
  }

  if(low_link[node] == init[node]) {
    std::vector<int> component;
    ++curr;
    while(st.back() != node) {
      level[st.back()] = curr;
      component.push_back(st.back());
      in_stack[st.back()] = 0;
      st.pop_back();
    }
    level[st.back()] = curr;
    in_stack[st.back()] = 0;
    st.pop_back();
  }
}

void extract() {
  st.clear();
  for(int i = 1;i <= n; i++)
    in_stack[i] = low_link[i] = init[i] = 0;
  int ptr = 1;
  for(int i = 1;i <= n; i++)
    if(low_link[i] == 0)
      dfs(i, ptr);
}


struct Info{
  int id;
  int a;
  int b;
  int c;
} v[5 + nmax];

bool compare1(Info f1, Info f2) {
  return f1.a < f2.a;
}

bool compare2(Info f1, Info f2) {
  return f1.b < f2.b;
}

bool compare3(Info f1, Info f2) {
  return f1.c < f2.c;
}

int aint[5 + 4 * nmax], ptr;
std::vector<std::pair<int,int>> edges;

void build(int node, int from, int to) {
  int mid = (from + to) / 2;
  if(from < to) {
    build(node * 2, from, mid);
    build(node * 2 + 1, mid + 1, to);
  }
  aint[node] = 0;
}

void update(int node, int from, int to, int x, int val) {
  if(from < to) {
    int mid = (from + to) / 2;
    if(x <= mid)
      update(node * 2, from, mid, x, val);
    else
      update(node * 2 + 1, mid + 1, to, x, val);
    aint[node] = ++ptr;
    if(0 < aint[node * 2])
      edges.push_back({aint[node], aint[node * 2]});
    if(0 < aint[node * 2 + 1])
      edges.push_back({aint[node], aint[node * 2 + 1]});
  } else 
    aint[node] = val;
}

void query(int node, int from, int to, int x, int y, int val) {
  if(from == x && to == y) {
    if(0 < aint[node])
      edges.push_back({val, aint[node]});
  } else {
    int mid = (from + to) / 2;
    if(x <= mid)
      query(node * 2, from, mid, x, std::min(y, mid), val);
    if(mid + 1 <= y)
      query(node * 2 + 1, mid + 1, to, std::max(mid + 1, x), y, val);
  }
}



int main() {
  std::ios::sync_with_stdio(0);
  std::cin.tie(0);

  int m;
  std::cin >> m;
  for(int i = 1;i <= m; i++) {
    std::cin >> v[i].a >> v[i].b >> v[i].c;
    v[i].id = i;
  }
  ptr = m;
  build(1, 1, m);

  std::sort(v + 1, v + m + 1, compare1);

  for(int i = 1;i <= m; i++) {
    update(1, 1, m, v[i].b, v[i].id);
    if(1 < v[i].b) 
      query(1, 1, m, 1, v[i].b - 1, v[i].id);
  }

  build(1, 1, m);
  for(int i = 1;i <= m; i++) {
    update(1, 1, m, v[i].c, v[i].id);
    if(1 < v[i].c) 
      query(1, 1, m, 1, v[i].c - 1, v[i].id);
  }

  std::sort(v + 1, v + m + 1, compare2);
  build(1, 1, m);
  for(int i = 1;i <= m; i++) {
    update(1, 1, m, v[i].c, v[i].id);
    if(1 < v[i].c) 
      query(1, 1, m, 1, v[i].c - 1, v[i].id);
  }

  SCC(ptr);

  for(int i = 0; i < edges.size(); i++)
    add_edge(edges[i].first, edges[i].second);

  extract();

  int q;
  std::cin >> q;

  for(int i = 1;i <= q; i++) {
    int x, y;
    std::cin >> x >> y;
    if(level[x] <= level[y]) {
      std::cout << "YES\n";
    } else
      std::cout << "NO\n";
  }
  return 0;
}
