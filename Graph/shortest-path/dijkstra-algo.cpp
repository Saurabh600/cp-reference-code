#include <bits/stdc++.h>
using namespace std;
using ll = int64_t;

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, m;
    cin >> n >> m;
    vector<vector<pair<ll, ll>>> g(n + 1);
    for (int i = 0; i < m; i++) {
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
    }

    vector<ll> dist(n + 1, -1);
    dist[1] = 0;

    vector<int> mark(n + 1, 0);

    priority_queue<pair<ll, ll>> pq;
    pq.push({0, 1});

    while (pq.size() > 0) {
        auto [_, u] = pq.top();
        pq.pop();

        if (mark[u] == 1) continue;
        mark[u] = 1;

        for (auto [v, wt] : g[u]) {
            if (dist[v] == -1 || dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                pq.push({-dist[v], v});
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }
    cout << '\n';

    return 0;
}
