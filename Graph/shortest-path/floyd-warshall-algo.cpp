#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

signed main() {
  ios::sync_with_stdio(false), cin.tie(0);
  ll n, m, q;
  cin >> n >> m >> q;

  const ll INF = 1e18;
  vector<vector<ll>> matrix(500, vector<ll>(500, INF));
  for (int i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    matrix[u][v] = min(matrix[u][v], w);
    matrix[v][u] = min(matrix[v][u], w);
  }

  for (int i = 0; i < n; i++) matrix[i][i] = 0;

  for (int k = 0; k < n; k++)
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++) {
        if (matrix[i][k] != INF && matrix[k][j] != INF)
          matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == INF) matrix[i][j] = -1;
    }
  }

  while (q--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    cout << matrix[a][b] << '\n';
  }

  return 0;
}
