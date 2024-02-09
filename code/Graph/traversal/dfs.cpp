#include <bits/stdc++.h>
using namespace std;

void dfs(int u, vector<int> adj[], vector<int> &vis, vector<int> &res) {
    vis[u] = 1;
    res.push_back(u);

    for (auto v : adj[u]) {
        if (!vis[v]) dfs(v, adj, vis, res);
    }
}

vector<int> dfsOfGraph(int V, vector<int> adj[]) {
    vector<int> res;
    vector<int> vis(V, 0);
    dfs(0, adj, vis, res);
    return res;
}
