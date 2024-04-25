#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

using T = pair<ll, ll>;
const ll INF = 1e18;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<vector<T>> g(n);
  int a, b, c;
  while (m--) {
    cin >> a >> b >> c;
    a--, b--;
    g[a].emplace_back(b, c);
  }

  priority_queue<T, vector<T>, greater<>> pq;
  vector<ll> dist(n, INF);

  dist[0] = 0;
  pq.emplace(0, 0);
  while (pq.size() > 0) {
    auto [dist_u, u] = pq.top();
    pq.pop();

    if (dist_u != dist[u]) continue;

    for (auto [v, w] : g[u]) {
      if (dist[v] > dist[u] + w) {
        dist[v] = dist[u] + w;
        pq.emplace(dist[v], v);
      }
    }
  }

  for (auto d : dist) cout << d << ' ';
  cout << '\n';

  return 0;
}
