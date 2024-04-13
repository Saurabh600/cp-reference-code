#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class M>
  SegTree(int _n, const vector<M>& arr, long long _nval = 0) : n(_n), nval(_nval) {
    tree.resize(4 * n + 1);
    build(1, 1, n, arr);
  }

  long long query(int l, int r) { return query(1, 1, n, l, r); }
  void update(int idx, long long val) { update(1, 1, n, idx, val); }

  private:
  std::vector<long long> tree;
  int n;
  long long nval;

  long long unite(long long a, long long b) { return min(a, b); }

  template <class M>
  void build(int i, int x, int y, const vector<M>& arr) {
    if (x == y) {
      tree[i] = arr[x];
    } else {
      int m = (x + y) >> 1;
      build(2 * i, x, m, arr);
      build(2 * i + 1, m + 1, y, arr);
      tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
    }
  }

  long long query(int i, int x, int y, int l, int r) {
    if (l <= x && r >= y) return tree[i];
    if (l > y || r < x) return nval;

    int m = (x + y) >> 1;
    return unite(query(2 * i, x, m, l, r), query(2 * i + 1, m + 1, y, l, r));
  }

  void update(int i, int x, int y, int idx, long long val) {
    if (x == y) {
      tree[i] = val;
    } else {
      int m = (x + y) >> 1;
      if (idx >= x && idx <= m) update(2 * i, x, m, idx, val);
      else update(2 * i + 1, m + 1, y, idx, val);
      tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
    }
  }
};

int main() {
  int n, q;
  cin >> n >> q;

  vector<int> arr(n + 1);
  for (int i = 1; i <= n; i++) cin >> arr[i];

  SegTree tree(n, arr, 1e18);

  while (q--) {
    int t;
    cin >> t;
    if (t == 1) {
      int k, u;
      cin >> k >> u;
      tree.update(k, u);
    } else {
      int l, r;
      cin >> l >> r;
      cout << tree.query(l, r) << '\n';
    }
  }

  return 0;
}
