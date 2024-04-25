#include <bits/stdc++.h>
using namespace std;

class dsu {
  vector<int> parent, size;

  public:
  dsu(int n) {
    parent.resize(n);
    size.resize(n);
    for (int v = 0; v < n; v++) {
      parent[v] = v;
      size[v] = 1;
    }
  }

  int get_size(int v) { return size[v]; }

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
