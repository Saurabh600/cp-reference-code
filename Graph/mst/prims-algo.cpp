#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
  int spanningTree(int V, vector<vector<int>> adj[]) {
    int sum = 0;
    vector<int> vis(V, 0);
    priority_queue<pair<int, int>> pq;
    pq.push({0, 0});

    while (!pq.empty()) {
      auto [dist, u] = pq.top();
      pq.pop();

      if (!vis[u]) {
        vis[u] = 1;
        sum += -dist;
        for (auto &it : adj[u]) {
          int v = it[0], wt = it[1];
          if (!vis[v]) pq.push({-wt, v});
        }
      }
    }

    return sum;
  }
};
