#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class T>
  SegTree(int size, T& A) : n(size) {
    tree.resize(4 * n);
    build(0, 0, n - 1, A);
  }

  int query(int qs, int qe, int k) { return query(0, 0, n - 1, qs, qe, k); }

  private:
  vector<vector<int>> tree;
  int n;

  template <class T>
  void build(int si, int ss, int se, T& A) {
    if (ss == se) {
      tree[si].push_back(A[ss]);
    } else {
      int mid = (ss + se) >> 1;
      build(2 * si + 1, ss, mid, A);
      build(2 * si + 2, mid + 1, se, A);
      merge(tree[2 * si + 1].begin(), tree[2 * si + 1].end(), tree[2 * si + 2].begin(),
            tree[2 * si + 2].end(), back_inserter(tree[si]));
    }
  }

  int query(int si, int ss, int se, int qs, int qe, int k) {
    if (qs <= ss && qe >= se) {
      return tree[si].end() - upper_bound(tree[si].begin(), tree[si].end(), k);
    }

    if (qs > se || qe < ss) return 0;

    int mid = (ss + se) >> 1;
    return query(2 * si + 1, ss, mid, qs, qe, k) + query(2 * si + 2, mid + 1, se, qs, qe, k);
  }
};
