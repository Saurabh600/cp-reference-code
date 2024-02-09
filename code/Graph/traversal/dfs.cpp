#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        vector<int> res;
        vector<int> vis(V, 0);
        dfs(0, adj, vis, res);
        return res;
    }

    void dfs(int node, vector<int> adj[], vector<int> &vis, vector<int> &res) {
        vis[node] = 1;
        res.push_back(node);

        for (auto it : adj[node]) {
            if (!vis[it]) dfs(it, adj, vis, res);
        }
    }
};
