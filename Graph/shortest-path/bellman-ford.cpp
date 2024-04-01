#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    vector<int> bellman_ford(int V, vector<vector<int>> &edges, int S) {
        vector<int> dist(V, 1e8);
        dist[S] = 0;
        // (n-1) times relaxation
        for (int i = 0; i < V - 1; i++) {
            // relaxation of (n-1) edges
            for (auto &edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                }
            }
        }

        // if further relaxation is possible, i.e negative cycle exists
        for (auto &edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            if (dist[u] != 1e8 && dist[u] + w < dist[v]) {
                return {-1};
            }
        }

        return dist;
    }
};
