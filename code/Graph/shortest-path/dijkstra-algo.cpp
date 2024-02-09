#include <bits/stdc++.h>
using namespace std;

class Solution {
    public:
    typedef pair<int, int> pi;
    // Function to find the shortest distance of all the vertices
    // from the source vertex S.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        priority_queue<pi, vector<pi>, greater<pi>> pq;
        pq.push({0, S});
        vector<int> dist(V, INT_MAX);
        dist[S] = 0;

        while (!pq.empty()) {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            for (auto &it : adj[node]) {
                int adjNode = it[0];
                int wt = it[1];

                if (dist[adjNode] > dist[node] + wt) {
                    dist[adjNode] = dist[node] + wt;
                    pq.push({dist[adjNode], adjNode});
                }
            }
        }

        return dist;
    }
};
