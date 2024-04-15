#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

class Solution {
  public:
  vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
    vector<vector<pi>> adj(N);
    for (auto &edge : edges) {
      adj[edge[0]].push_back({edge[1], edge[2]});
    }

    vector<int> vis(N, 0);
    stack<int> stk;

    topoSort(0, adj, vis, stk);

    vector<int> dist(N, INT_MAX);
    dist[0] = 0;
    while (!stk.empty()) {
      auto node = stk.top();
      stk.pop();

      for (auto &pr : adj[node]) {
        int it = pr.first;
        int wt = pr.second;
        dist[it] = min(dist[it], dist[node] + wt);
      }
    }

    for (auto &d : dist) {
      if (d == INT_MAX) d = -1;
    }

    return dist;
  }

  void topoSort(int node, vector<vector<pair<int, int>>> &adj, vector<int> &vis, stack<int> &stk) {
    vis[node] = 1;

    for (auto &pr : adj[node]) {
      int it = pr.first;
      if (!vis[it]) topoSort(it, adj, vis, stk);
    }

    stk.push(node);
  }
};
