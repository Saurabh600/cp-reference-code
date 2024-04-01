#include <bits/stdc++.h>
using namespace std;

vector<int> topoSort(int V, vector<int> adj[]) {
    vector<int> deg(V, 0);
    for (int i = 0; i < V; i++) {
        for (int u : adj[i]) deg[u]++;
    }

    vector<int> res;
    queue<int> q;

    for (int i = 0; i < V; i++) {
        if (!deg[i]) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        res.push_back(u);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) q.push(v);
        }
    }

    return res;
}
