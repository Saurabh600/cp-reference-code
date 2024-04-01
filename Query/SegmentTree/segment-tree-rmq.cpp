#include <bits/stdc++.h>
using namespace std;

template <class T>
class SegTree {
  public:
  template <class M>
  SegTree(int _n, const vector<M>& arr, T _nval = 0) : n(_n), nval(_nval) {
    tree.resize(4 * n);
    build(0, 0, n - 1, arr);
  }

  T query(int l, int r) { return query(0, 0, n - 1, l, r); }
  void update(int idx, int val) { point_update(0, 0, n - 1, idx, val); }

  private:
  vector<T> tree;
  int n;
  T nval;

  template <class M>
  void build(int i, int x, int y, const vector<M>& arr) {
    if (x == y) {
      tree[i] = arr[x];
    } else {
      int m = (x + y) >> 1;
      build(2 * i + 1, x, m, arr);
      build(2 * i + 2, m + 1, y, arr);
      tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  T query(int i, int x, int y, int l, int r) {
    if (l <= x && r >= y) return tree[i];
    if (l > y || r < x) return nval;

    int m = (x + y) >> 1;
    return min(query(2 * i + 1, x, m, l, r), query(2 * i + 2, m + 1, y, l, r));
  }

  void point_update(int i, int x, int y, int idx, int val) {
    if (x == y) {
      tree[i] = val;
    } else {
      int m = (x + y) >> 1;
      if (idx >= x && idx <= m) point_update(2 * i + 1, x, m, idx, val);
      else point_update(2 * i + 2, m + 1, y, idx, val);
      tree[i] = min(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> arr(n);
  for (auto& i : arr) cin >> i;

  SegTree<int> tree(n, arr, 1e9);

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
      cout << tree.query(l - 1, r - 1) << '\n';
    }
  }
  return 0;
}
