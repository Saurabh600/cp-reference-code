#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<int> vis, vector<int> &res) {
  vis[node] = 1;
  for (int it : adj[node]) {
    if (!vis[it]) dfs(it, adj, vis, res);
  }
  res.push_back(node);
}

vector<int> topoSort(int V, vector<int> adj[]) {
  vector<int> res;
  vector<int> vis(V, 0);
  for (int i = 0; i < V; i++) {
    if (!vis[i]) {
      dfs(i, adj, vis, res);
    }
  }
  reverse(res.begin(), res.end());
  return res;
}
