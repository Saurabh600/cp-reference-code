#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class T>
  SegTree(int size, T& A, long long def_value = 0) : n(size), iota(def_value) {
    tree.resize(4 * n + 1);
    build(1, 1, n, A);
  }

  long long query(int qs, int qe) { return query(1, 1, n, qs, qe); }
  void update(int arrInd, long long value) { update(1, 1, n, arrInd, value); }

  private:
  vector<long long> tree;
  int n;
  long long iota;

  long long unite(long long a, long long b) { return min(a, b); }

  template <class T>
  void build(int si, int ss, int se, T& A) {
    if (ss == se) {
      tree[si] = A[ss];
    } else {
      int mid = (ss + se) >> 1;
      build(si << 1, ss, mid, A);
      build((si << 1) | 1, mid + 1, se, A);
      tree[si] = unite(tree[si << 1], tree[(si << 1) | 1]);
    }
  }

  long long query(int si, int ss, int se, int qs, int qe) {
    if (qs <= ss && qe >= se) return tree[si];
    if (qs > se || qe < ss) return iota;

    int mid = (ss + se) >> 1;
    return unite(query(si << 1, ss, mid, qs, qe), query((si << 1) | 1, mid + 1, se, qs, qe));
  }

  void update(int si, int ss, int se, int arrInd, long long value) {
    if (ss == se) {
      tree[si] = value;
    } else {
      int mid = (ss + se) >> 1;
      if (arrInd >= ss && arrInd <= mid) update(si << 1, ss, mid, arrInd, value);
      else update((si << 1) | 1, mid + 1, se, arrInd, value);
      tree[si] = unite(tree[si << 1], tree[(si << 1) | 1]);
    }
  }
};
