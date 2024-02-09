#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    vector<int> shortestPath(vector<vector<int>> &edges, int N, int M,
                             int src) {
        vector<vector<int>> g(N);
        for (auto &edge : edges) {
            g[edge[0]].push_back(edge[1]);
            g[edge[1]].push_back(edge[0]);
        }

        queue<int> q;
        q.push(src);

        vector<int> dist(N, INT_MAX);
        dist[src] = 0;
        /* for unit weight simple bfs is sufficient too */
        // vector<int> vis(N, 0);
        // vis[src] = 1;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (int it : g[node]) {
                if (dist[it] > dist[node] + 1) {
                    dist[it] = dist[node] + 1;
                    q.push(it);
                }
            }

            /* BFS Approach */
            // for (int it: adj[node]) {
            //     if (!vis[it]) {
            //         dist[it] = dist[node] + 1;
            //         vis[it] = 1;
            //         q.push(it);
            //     }
            // }
        }

        for (int &it : dist) {
            if (it == INT_MAX) it = -1;
        }

        return dist;
    }
};
