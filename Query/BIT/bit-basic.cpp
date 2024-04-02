#include <bits/stdc++.h>

class FenwickTree {
  private:
  std::vector<long long> tree;
  int n;

  public:
  FenwickTree(int _n) : n(_n) { tree.assign(n + 1, 0); }

  template <class M>
  FenwickTree(int _n, const std::vector<M>& arr) : n(_n) {
    tree.assign(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      tree[i] += arr[i - 1];
      int rsb = i & -i;
      if (i + rsb <= n) tree[i + rsb] += tree[i];
    }
  }

  long long get(int i) {
    long long sum = 0;
    for (; i > 0; i -= i & -i) sum += tree[i];
    return sum;
  }

  void update(int i, long long x) {
    for (; i <= n; i += i & -i) tree[i] += x;
  }

  long long get(int l, int r) { return get(r) - get(l - 1); }
};
