#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pi;

class Solution {
    public:
    vector<int> dijkstra(int V, vector<vector<pi>> adj, int s) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        vector<int> dist(V, INT_MAX);

        pq.push({0, s});
        dist[s] = 0;

        while (!pq.empty()) {
            auto [_, u] = pq.top();
            pq.pop();

            for (auto &[v, wt] : adj[u]) {
                if (dist[v] > dist[u] + wt) {
                    dist[v] = dist[u] + wt;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};
