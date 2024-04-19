#include <bits/stdc++.h>
using namespace std;

struct DisjointSet {
  public:
  vector<int> parent, size;

  DisjointSet(int n) {
    parent.resize(n);
    size.resize(n);
    for (int v = 0; v < n; v++) {
      parent[v] = v;
      size[v] = 1;
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
      if (size[a] < size[b]) swap(a, b);
      parent[b] = a;
      size[a] += size[b];
    }
  }
};
