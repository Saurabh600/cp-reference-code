#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        typedef pair<int, int> pi;
        int sum = 0;
        vector<int> vis(V, 0);
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, 0});

        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();

            int wt = it.first;
            int node = it.second;

            if (vis[node] == 1) continue;
            vis[node] = 1;
            sum += wt;

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int adjWt = it[1];

                if (!vis[adjNode]) {
                    pq.push({adjWt, adjNode});
                }
            }
        }

        return sum;
    }
};
