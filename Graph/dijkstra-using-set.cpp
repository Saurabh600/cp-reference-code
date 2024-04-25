#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef long double ld;
typedef pair<ll, ll> pii;

const ll INF = 1e18;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<pii>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g[u].emplace_back(v, w);
    g[v].emplace_back(u, w);
  }

  auto dijkstra = [&](int src) -> vector<ll> {
    vector<ll> dist(n, INF);
    set<pii> s;
    dist[src] = 0;
    for (int i = 0; i < n; i++) s.emplace(dist[i], i);

    while (s.size() > 0) {
      auto node = s.begin()->second;
      s.erase(s.begin());

      for (auto [nxt, wt] : g[node]) {
        auto curr = dist[node] + wt;
        if (dist[nxt] > curr) {
          s.erase({dist[nxt], nxt});
          dist[nxt] = curr;
          s.emplace(dist[nxt], nxt);
        }
      }
    }

    return dist;
  };

  return 0;
}
