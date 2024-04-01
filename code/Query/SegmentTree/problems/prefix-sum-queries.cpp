#include <bits/stdc++.h>
using namespace std;

class segtree {
  public:
  struct node {
    int64_t sum = 0;
    int64_t pref = 0;
    void apply(int v) {
      sum = v;
      pref = max(v, 0);
    }
  };
  node unite(const node &n1, const node &n2) const {
    node res;
    res.sum = (n1.sum + n2.sum);
    res.pref = max(n1.pref, n1.sum + n2.pref);
    return res;
  }

  int n;
  vector<node> tree;

  template <class M>
  segtree(const vector<M> &v) {
    n = v.size();
    assert(n > 0);
    tree.resize(4 * n);
    build(0, 0, n - 1, v);
  }

  template <class M>
  void build(int i, int l, int r, const vector<M> &v) {
    if (l == r) {
      tree[i].apply(v[l]);
    } else {
      int m = (l + r) >> 1;
      build(2 * i + 1, l, m, v);
      build(2 * i + 2, m + 1, r, v);
      tree[i] = unite(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  node get(int i, int x, int y, int l, int r) {
    if (x >= l && y <= r) return tree[i];
    if (r < x || l > y) return node{};

    int m = (x + y) >> 1;
    return unite(get(2 * i + 1, x, m, l, r), get(2 * i + 2, m + 1, y, l, r));
  }

  void point_update(int i, int l, int r, int idx, int val) {
    if (l == r) {
      tree[i].apply(val);
    } else {
      int m = (l + r) >> 1;
      if (idx >= l && idx <= m) point_update(2 * i + 1, l, m, idx, val);
      else point_update(2 * i + 2, m + 1, r, idx, val);
      tree[i] = unite(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  node get(int l, int r) {
    return get(0, 0, n - 1, l, r);
  }
  void point_update(int idx, int val) {
    point_update(0, 0, n - 1, idx, val);
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int64_t> v(n);
  for (auto &i : v) cin >> i;
  segtree seg(v);
  while (q--) {
    int t;
    cin >> t;
    if (t == 2) {
      int a, b;
      cin >> a >> b;
      cout << seg.get(a - 1, b - 1).pref << '\n';
    } else {
      int k, u;
      cin >> k >> u;
      seg.point_update(k - 1, u);
    }
  }
  return 0;
}
