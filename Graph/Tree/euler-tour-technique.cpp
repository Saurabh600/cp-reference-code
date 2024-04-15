/**
  author: Saurabh Chaudhary (Saurabh600)
  created: 15.04.2024 15:19:40
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#ifdef LOCAL_RUN
#include "debug.h"
#else
#define debug(...) 42
#endif

signed main() {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;

  vector<vector<int>> g(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  int timer = 1;
  vector<int> flatTree(2 * n + 1), enter(n + 1), leave(n + 1);

  function<void(int, int)> dfs = [&](int node, int par) -> void {
    enter[node] = timer;
    flatTree[timer] = node;
    timer++;

    for (auto adj : g[node]) {
      if (adj != par) dfs(adj, node);
    }

    leave[node] = timer;
    flatTree[timer] = node;
    timer++;
  };

  dfs(1, -1);

  return 0;
}
