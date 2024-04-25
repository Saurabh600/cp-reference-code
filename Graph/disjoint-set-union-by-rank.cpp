#include <bits/stdc++.h>
using namespace std;

struct dsu {
  vector<int> parent, rank;

  public:
  dsu(int n) {
    parent.resize(n);
    rank.resize(n);
    for (int v = 0; v < n; v++) {
      parent[v] = v;
      rank[v] = 0;
    }
  }

  int find(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find(parent[v]);
  }

  void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) {
      if (rank[a] < rank[b]) swap(a, b);
      parent[b] = a;
      if (rank[a] == rank[b]) rank[a]++;
    }
  }
};
