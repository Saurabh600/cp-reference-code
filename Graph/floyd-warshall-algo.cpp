#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

signed main() {
  ios::sync_with_stdio(false), cin.tie(0);
  ll n, m, q;
  cin >> n >> m >> q;

  const ll INF = 1e18;
  vector<vector<ll>> dp(500, vector<ll>(500, INF));

  for (int i = 0; i < m; i++) {
    ll u, v, w;
    cin >> u >> v >> w;
    --u, --v;
    dp[u][v] = min(dp[u][v], w);
    dp[v][u] = min(dp[v][u], w);
  }

  for (int i = 0; i < n; i++) dp[i][i] = 0;

  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dp[i][k] != INF && dp[k][j] != INF) {
          dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
        }
      }
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (dp[i][j] == INF) dp[i][j] = -1;
    }
  }

  return 0;
}
