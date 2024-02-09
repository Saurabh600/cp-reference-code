#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        vector<int> path(V, 0);
        for (int i = 0; i < V; i++) {
            if (!vis[i] && dfs(i, adj, vis, path)) return true;
        }

        return false;
    }

    bool dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &path) {
        vis[node] = 1;
        path[node] = 1;
        for (int it : adj[node]) {
            if (vis[it] && path[it]) return true;
            if (!vis[it] && dfs(it, adj, vis, path)) return true;
        }

        path[node] = 0;
        return false;
    }
};
