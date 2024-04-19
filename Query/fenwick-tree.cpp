#include <bits/stdc++.h>
using namespace std;

class FenwickTree {
  private:
  vector<long long> tree;
  int n;

  public:
  FenwickTree(int size) : n(size + 1) { tree.assign(n, 0); }

  template <class T>
  FenwickTree(int size, T& A) : FenwickTree(size) {
    for (int i = 1; i < n; i++) {
      tree[i] += A[i - 1];
      int rsb = i & -i;
      if (i + rsb < n) tree[i + rsb] += tree[i];
    }
  }

  long long get(int i) {
    long long sum = 0;
    for (; i > 0; i -= i & -i) sum += tree[i];
    return sum;
  }

  void update(int i, long long x) {
    for (; i < n; i += i & -i) tree[i] += x;
  }

  long long get(int l, int r) { return get(r) - get(l - 1); }
};
