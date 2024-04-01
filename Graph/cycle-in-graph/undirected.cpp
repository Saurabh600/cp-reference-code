#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        for (int i = 0; i < V; i++) {
            // if (!vis[i] && bfs(i, adj, vis)) return true;
            if (!vis[i] && dfs(i, -1, adj, vis)) return true;
        }

        return false;
    }

    bool dfs(int node, int parent, vector<int> adj[], vector<int> &vis) {
        vis[node] = 1;
        for (int it : adj[node]) {
            if (vis[it] && it != parent) return true;
            if (!vis[it] && dfs(it, node, adj, vis)) return true;
        }
        return false;
    }

    bool bfs(int i, vector<int> adj[], vector<int> &vis) {
        queue<pair<int, int>> q;
        q.push({i, -1});
        vis[i] = 1;
        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();
            for (int it : adj[node]) {
                if (vis[it] && it != parent) return true;
                if (!vis[it]) {
                    vis[it] = 1;
                    q.push({it, node});
                }
            }
        }

        return false;
    }
};
