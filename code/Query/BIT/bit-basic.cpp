#include <bits/stdc++.h>

template <class T>
class FenwickTree {
  public:
  std::vector<T> bit;
  int n;

  template <class M>
  FenwickTree(std::vector<M>& v) {
    n = v.size();
    bit.resize(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      bit[i] += v[i - 1];
      T rsb = i & (-i);
      if (i + rsb <= n) {
        bit[i + rsb] += bit[i];
      }
    }
  }

  FenwickTree(int n) {
    this->n = n;
    bit.resize(n + 1, 0);
  }

  T get(int i) {
    T sum = 0;
    for (; i > 0; i -= i & (-i)) {
      sum += bit[i];
    }
    return sum;
  }

  void update(int i, int x) {
    for (; i <= n; i += i & (-i)) {
      bit[i] += x;
    }
  }

  T get(int l, int r) {
    return get(r) - get(l - 1);
  }
};
