#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  struct SegNode {
    long long mn = 1e18;

    void apply(long long v) { mn = v; }

    SegNode operator+(SegNode other) const {
      SegNode res;
      res.mn = min(this->mn, other.mn);
      return res;
    }
  };

  template <class T>
  SegTree(int size, T &A) : n(size) {
    tree.resize(4 * n);
    build(0, 0, n - 1, A);
  }

  SegNode query(int qs, int qe) { return query(0, 0, n - 1, qs, qe); }
  void update(int arrInd, long long value) { update(0, 0, n - 1, arrInd, value); }

  private:
  int n;
  vector<SegNode> tree;

  template <class T>
  void build(int si, int ss, int se, T &A) {
    if (ss == se) {
      tree[si].apply(A[ss]);
    } else {
      int mid = (ss + se) >> 1;
      build(2 * si + 1, ss, mid, A);
      build(2 * si + 2, mid + 1, se, A);
      tree[si] = tree[2 * si + 1] + tree[2 * si + 2];
    }
  }

  SegNode query(int si, int ss, int se, int qs, int qe) {
    if (ss >= qs && se <= qe) return tree[si];
    if (qe < ss || qs > se) return SegNode{};

    int mid = (ss + se) >> 1;
    return query(2 * si + 1, ss, mid, qs, qe) + query(2 * si + 2, mid + 1, se, qs, qe);
  }

  void update(int si, int ss, int se, int arrInd, long long value) {
    if (ss == se) {
      tree[si].apply(value);
    } else {
      int mid = (ss + se) >> 1;
      if (arrInd >= ss && arrInd <= mid) update(2 * si + 1, ss, mid, arrInd, value);
      else update(2 * si + 2, mid + 1, se, arrInd, value);
      tree[si] = tree[2 * si + 1] + tree[2 * si + 2];
    }
  }
};
