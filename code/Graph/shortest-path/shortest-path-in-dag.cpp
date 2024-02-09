#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    vector<int> shortestPath(int N, int M, vector<vector<int>> &edges) {
        vector<vector<pair<int, int>>> adj(N);
        for (auto &edge : edges) {
            adj[edge[0]].push_back({edge[1], edge[2]});
        }

        vector<int> vis(N, 0);
        stack<int> st;

        topoSort(0, adj, vis, st);

        vector<int> dist(N, INT_MAX);
        dist[0] = 0;
        while (!st.empty()) {
            auto node = st.top();
            st.pop();

            for (auto &pr : adj[node]) {
                int it = pr.first;
                int wt = pr.second;
                dist[it] = min(dist[it], dist[node] + wt);
            }
        }

        for (auto &d : dist) {
            if (d == INT_MAX) d = -1;
        }

        return dist;
    }

    void topoSort(int node, vector<vector<pair<int, int>>> &adj,
                  vector<int> &vis, stack<int> &st) {
        vis[node] = 1;

        for (auto &pr : adj[node]) {
            int it = pr.first;
            if (!vis[it]) topoSort(it, adj, vis, st);
        }

        st.push(node);
    }
};
