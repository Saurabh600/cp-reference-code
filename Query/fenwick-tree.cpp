#include <bits/stdc++.h>
using namespace std;

template <class T = int>
struct fenwick {
  T n;
  vector<T> tree;

  fenwick(T _n) : n(_n + 1) {
    assert(is_integral<T>().value);
    tree.assign(n, 0);
  }

  template <class U>
  fenwick(T _n, const U& A) : fenwick(_n) {
    for (T i = 1; i < n; i++) {
      tree[i] += A[i - 1];
      T rsb = i & -i;
      if (i + rsb < n) tree[i + rsb] += tree[i];
    }
  }

  T query(T i) {
    T sum = 0;
    for (; i > 0; i -= i & -i) sum += tree[i];
    return sum;
  }

  void update(T i, T val) {
    assert(i > 0);
    for (; i < n; i += i & -i) tree[i] += val;
  }

  T query(T l, T r) { return query(r) - query(l - 1); }
};
