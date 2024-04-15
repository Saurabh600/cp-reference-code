#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class T>
  SegTree(int size, T& A, long long def_value = 0) : n(size), iota(def_value) {
    tree.resize(4 * n);
    lazy.resize(4 * n);
    build(0, 0, n - 1, A);
  }

  long long query(int qs, int qe) { return query(0, 0, n - 1, qs, qe); }
  void range_update(int qs, int qe, long long value) { range_update(0, 0, n - 1, qs, qe, value); }

  private:
  vector<long long> tree;
  vector<long long> lazy;
  int n;
  long long iota;

  long long unite(long long a, long long b) { return min(a, b); }

  template <class T>
  void build(int si, int ss, int se, T& A) {
    if (ss == se) {
      tree[si] = A[ss];
    } else {
      int mid = (ss + se) >> 1;
      build(2 * si + 1, ss, mid, A);
      build(2 * si + 2, mid + 1, se, A);
      tree[si] = unite(tree[2 * si + 1], tree[2 * si + 2]);
    }
  }

  long long query(int si, int ss, int se, int qs, int qe) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];
      if (ss != se) {
        lazy[2 * si + 1] += lazy[si];
        lazy[2 * si + 2] += lazy[si];
      }
      lazy[si] = 0;
    }

    if (qs <= ss && qe >= se) return tree[si];
    if (qs > se || qe < ss) return iota;

    int mid = (ss + se) >> 1;
    return unite(query(2 * si + 1, ss, mid, qs, qe), query(2 * si + 2, mid + 1, se, qs, qe));
  }

  void range_update(int si, int ss, int se, int qs, int qe, long long value) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];
      if (ss != se) {
        lazy[2 * si + 1] += lazy[si];
        lazy[2 * si + 2] += lazy[si];
      }
      lazy[si] = 0;
    }

    if (qs > se || qe < ss || ss > se) return;
    if (ss >= qs && se <= qe) {
      tree[si] += (se - ss + 1) * value;
      if (ss != se) {
        lazy[2 * si + 1] += value;
        lazy[2 * si + 2] += value;
      }
      return;
    }

    int mid = (ss + se) >> 1;
    range_update(2 * si + 1, ss, mid, qs, qe, value);
    range_update(2 * si + 2, mid + 1, se, qs, qe, value);
    tree[si] = unite(tree[2 * si + 1], tree[2 * si + 2]);
  }
};
