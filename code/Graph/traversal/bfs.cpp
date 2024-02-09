#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        vector<int> res;
        vector<int> vis(V, 0);
        queue<int> q;

        q.push(0);
        vis[0] = 1;
        res.push_back(0);

        while (!q.empty()) {
            auto node = q.front();
            q.pop();
            for (auto it : adj[node]) {
                if (!vis[it]) {
                    q.push(it);
                    vis[it] = 1;
                    res.push_back(it);
                }
            }
        }

        return res;
    }
};
