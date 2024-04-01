#include <bits/stdc++.h>
using namespace std;

const int inf = int(1e9);

class SegTree {
  public:
  struct node {
    int mn = inf;
    void apply(int v) { mn = v; }
  };

  template <class M>
  SegTree(int _n, const vector<M> &arr) : n(_n) {
    tree.resize(4 * n);
    build(0, 0, n - 1, arr);
  }

  node query(int l, int r) { return query(0, 0, n - 1, l, r); }
  void update(int idx, int64_t val) { point_update(0, 0, n - 1, idx, val); }

  private:
  int n;
  vector<node> tree;

  node unite(const node &n1, const node &n2) const {
    node res;
    res.mn = min(n1.mn, n2.mn);
    return res;
  }

  template <class M>
  void build(int i, int x, int y, const vector<M> &arr) {
    if (x == y) {
      tree[i].apply(arr[x]);
    } else {
      int m = (x + y) >> 1;
      build(2 * i + 1, x, m, arr);
      build(2 * i + 2, m + 1, y, arr);
      tree[i] = unite(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  node query(int i, int x, int y, int l, int r) {
    if (x >= l && y <= r) return tree[i];
    if (r < x || l > y) return node{};

    int m = (x + y) >> 1;
    return unite(query(2 * i + 1, x, m, l, r), query(2 * i + 2, m + 1, y, l, r));
  }

  void point_update(int i, int x, int y, int idx, int64_t val) {
    if (x == y) {
      tree[i].apply(val);
    } else {
      int m = (x + y) >> 1;
      if (idx >= x && idx <= m) point_update(2 * i + 1, x, m, idx, val);
      else point_update(2 * i + 2, m + 1, y, idx, val);
      tree[i] = unite(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (int &i : arr) cin >> i;

  SegTree tree(n, arr);

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int k, u;
      cin >> k >> u;
      tree.update(k - 1, u);
    } else {
      int l, r;
      cin >> l >> r;
      cout << tree.query(l - 1, r - 1).mn << '\n';
    }
  }
  return 0;
}
