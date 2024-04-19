#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, q;
  cin >> n >> q;

  // taking graph input (1 indexed)
  vector<vector<int>> g(n + 1);
  for (int i = 1; i < n; i++) {
    int u, v;
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // parent and depth of all node
  vector<int> parent(n + 1);
  vector<int> depth(n + 1);

  // dfs implementation
  function<void(int, int)> dfs = [&](int node, int par) -> void {
    parent[node] = par;
    if (par != -1) depth[node] = depth[par] + 1;
    for (int adj : g[node]) {
      if (adj == par) continue;
      dfs(adj, node);
    }
  };

  // making dfs call
  dfs(1, -1);

  // creating dp for binary lifting
  int LOG = log2(n) + 1;
  vector<vector<int>> dp(n + 1, vector<int>(LOG, -1));
  for (int j = 0; j < LOG; j++) {
    for (int i = 1; i <= n; i++) {
      if (j == 0) dp[i][j] = parent[i];
      else if (dp[i][j - 1] != -1) dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
  }

  // get kth parent of x
  auto kth_parent = [&](int x, int k) -> int {
    for (int j = LOG - 1; j >= 0; j--) {
      if (k & (1 << j)) x = dp[x][j];
    }
    return x;
  };

  // get lca of a & b
  auto lca = [&](int a, int b) -> int {
    if (depth[a] < depth[b]) swap(a, b);
    int k = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; j--) {
      if (k & (1 << j)) a = dp[a][j];
    }
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; j--) {
      if (dp[a][j] != dp[b][j]) a = dp[a][j], b = dp[b][j];
    }
    return dp[a][0];
  };

  while (q--) {
    int a, b;
    cin >> a >> b;
    // path distance between a & b
    cout << (depth[a] + depth[b] - 2 * depth[lca(a, b)]) << '\n';
  }

  return 0;
}
