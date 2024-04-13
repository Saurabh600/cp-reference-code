#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class M>
  SegTree(int _n, const vector<M>& arr, long long _nval = 0) : n(_n), nval(_nval) {
    tree.assign(4 * n + 1, 0);
    lazy.assign(4 * n + 1, 0);
    build(1, 1, n, arr);
  }

  long long query(int l, int r) { return query(1, 1, n, l, r); }
  void range_update(int l, int r, long long val) { range_update(1, 1, n, l, r, val); }

  private:
  vector<long long> tree;
  vector<long long> lazy;
  int n;
  long long nval;

  long long unite(long long a, long long b) { return min(a, b); }

  template <class M>
  void build(int i, int x, int y, const vector<M>& arr) {
    if (x == y) {
      tree[i] = arr[x];
    } else {
      int mid = (x + y) >> 1;
      build(2 * i, x, mid, arr);
      build(2 * i + 1, mid + 1, y, arr);
      tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
    }
  }

  long long query(int i, int x, int y, int l, int r) {
    if (lazy[i] != 0) {
      tree[i] += (y - x + 1) * lazy[i];
      if (x != y) {
        lazy[2 * i] += lazy[i];
        lazy[2 * i + 1] += lazy[i];
      }
      lazy[i] = 0;
    }

    if (l <= x && r >= y) return tree[i];
    if (l > y || r < x) return nval;

    int m = (x + y) >> 1;
    return unite(query(2 * i, x, m, l, r), query(2 * i + 1, m + 1, y, l, r));
  }

  void range_update(int i, int x, int y, int l, int r, long long val) {
    if (lazy[i] != 0) {
      tree[i] += (y - x + 1) * lazy[i];
      if (x != y) {
        lazy[2 * i] += lazy[i];
        lazy[2 * i + 1] += lazy[i];
      }
      lazy[i] = 0;
    }

    if (l > y || r < x || x > y) return;
    if (x >= l && y <= r) {
      tree[i] += (y - x + 1) * val;
      if (x != y) {
        lazy[2 * i] += val;
        lazy[2 * i + 1] += val;
      }
      return;
    }

    int m = (x + y) >> 1;
    range_update(2 * i, x, m, l, r, val);
    range_update(2 * i + 1, m + 1, y, l, r, val);
    tree[i] = unite(tree[2 * i], tree[2 * i + 1]);
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
      int l, r, u;
      cin >> l >> r >> u;
      tree.range_update(l, r, u);
    } else {
      int k;
      cin >> k;
      cout << tree.query(k, k) << '\n';
    }
  }

  return 0;
}
