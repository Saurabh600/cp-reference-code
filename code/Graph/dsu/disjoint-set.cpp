#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> parent, rank;

    public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int node) {
        if (parent[node] == node) return node;

        int root = node;
        while (parent[root] != root) {
            root = parent[root];
        }

        while (node != root) {
            int next = parent[node];
            node = parent[node];
            node = next;
        }

        return root;
    }

    void unite(int u, int v) {
        int root_u = find(u);
        int root_v = find(v);

        if (root_u == root_v) return;

        if (rank[root_u] < rank[root_v]) {
            parent[root_u] = root_v;
        } else if (rank[root_v] > rank[root_u]) {
            parent[root_v] = root_u;
        } else {
            parent[root_u] = root_v;
            rank[root_v]++;
        }
    }
};
