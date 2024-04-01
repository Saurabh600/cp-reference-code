#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
  private:
  vector<int> parent, rank;

  public:
  DisjointSet(int n) {
    parent.resize(n);
    rank.resize(n, 0);
    for (int i = 0; i < n; i++) parent[i] = i;
  }

  int find(int node) {
    if (parent[node] == node) return node;
    return parent[node] = find(parent[node]);
  }

  bool unite(int u, int v) {
    int pu = find(u), pv = find(v);
    if (pu == pv) return false;

    if (rank[pu] < rank[pv]) parent[pu] = pv;
    else if (rank[pv] < rank[pu]) parent[pv] = pu;
    else parent[pu] = pv, rank[pv]++;

    return true;
  }
};
