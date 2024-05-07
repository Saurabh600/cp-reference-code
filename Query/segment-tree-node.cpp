#include <bits/stdc++.h>
using namespace std;

struct node {
  long long mn = LLONG_MAX;

  void apply(long long v) { mn = v; }

  node operator+(const node &other) const {
    node res;
    res.mn = min(mn, other.mn);
    return res;
  }
};

class seg_tree {
  public:
  template <class T>
  seg_tree(int _n, const T &A) : n(_n) {
    tree.resize(n << 2);
    build(0, 0, n - 1, A);
  }

  node query(int l, int r) { return query(0, 0, n - 1, l, r); }
  void update(int pos, long long val) { update(0, 0, n - 1, pos, val); }

  private:
  int n;
  vector<node> tree;

  template <class T>
  void build(int i, int x, int y, const T &arr) {
    if (x == y) {
      tree[i].apply(arr[x]);
    } else {
      int m = (x + y) >> 1;
      build(2 * i + 1, x, m, arr);
      build(2 * i + 2, m + 1, y, arr);
      tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
  }

  node query(int i, int x, int y, int l, int r) {
    if (r < x || l > y || l > r) return node{};
    if (x >= l && y <= r) return tree[i];
    int m = (x + y) >> 1;
    return query(2 * i + 1, x, m, l, r) + query(2 * i + 2, m + 1, y, l, r);
  }

  void update(int i, int x, int y, int pos, long long val) {
    if (x == y) {
      tree[i].apply(val);
    } else {
      int mid = (x + y) >> 1;
      if (pos >= x && pos <= mid) update(2 * i + 1, x, mid, pos, val);
      else update(2 * i + 2, mid + 1, y, pos, val);
      tree[i] = tree[2 * i + 1] + tree[2 * i + 2];
    }
  }
};
