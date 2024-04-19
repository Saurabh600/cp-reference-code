#include <bits/stdc++.h>
using namespace std;

const int NAX = 1e6;
const int LOG = 21;

int up[NAX][LOG], level[NAX];
int in[NAX], out[NAX], ft[NAX << 1], sub[NAX];

vector<vector<int>> g;
int counter = 0;

void dfs(int u, int par, int lvl) {
  in[u] = counter;
  ft[counter] = u;
  counter++;

  level[u] = lvl;
  up[u][0] = par;
  sub[u] = 1;

  for (auto v : g[u]) {
    if (v != par) {
      dfs(v, u, lvl + 1);
      sub[u] += sub[v];
    }
  }

  out[u] = counter;
  ft[counter] = u;
  counter++;
}

int findKthAncestor(int u, int k) {
  for (int j = LOG - 1; j >= 0; j--) {
    if (k & (1 << j)) u = up[u][j];
  }
  return u;
}

int findLCA(int a, int b) {
  if (level[a] < level[b]) swap(a, b);
  a = findKthAncestor(a, level[a] - level[b]);

  if (a == b) return a;
  for (int j = LOG - 1; j >= 0; j--) {
    if (up[a][j] != up[b][j]) a = up[a][j], b = up[b][j];
  }

  return up[a][0];
}

void preprocess(int N) {
  counter = 0;
  dfs(0, -1, 0);

  for (int j = 1; j < LOG; j++) {
    for (int i = 0; i < N; i++) {
      if (up[i][j - 1] != -1) up[i][j] = up[up[i][j - 1]][j - 1];
    }
  }
}
