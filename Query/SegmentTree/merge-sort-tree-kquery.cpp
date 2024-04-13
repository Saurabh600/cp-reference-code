#include <bits/stdc++.h>
using namespace std;

class SegTree {
  public:
  template <class M>
  SegTree(int size, const vector<M>& arr) : n(size) {
    tree.resize(4 * n);
    build(0, 0, n - 1, arr);
  }

  int query(int l, int r, int k) { return query(0, 0, n - 1, l, r, k); }

  private:
  vector<vector<int>> tree;
  int n;

  vector<int> merge(const vector<int>& v1, const vector<int>& v2) {
    vector<int> merged;
    merged.resize(v1.size() + v2.size());
    std::merge(v1.begin(), v1.end(), v2.begin(), v2.end(), merged.begin());
    return merged;
  }

  template <class M>
  void build(int i, int x, int y, const vector<M>& arr) {
    if (x == y) {
      tree[i].push_back(arr[x]);
    } else {
      int m = (x + y) >> 1;
      build(2 * i + 1, x, m, arr);
      build(2 * i + 2, m + 1, y, arr);
      tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
    }
  }

  int query(int i, int x, int y, int l, int r, int k) {
    if (l <= x && r >= y) {
      return tree[i].end() - upper_bound(tree[i].begin(), tree[i].end(), k);
    }

    if (l > y || r < x) return 0;

    int m = (x + y) >> 1;
    return query(2 * i + 1, x, m, l, r, k) + query(2 * i + 2, m + 1, y, l, r, k);
  }
};

signed main() {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n;
  cin >> n;
  vector<int> arr(n);
  for (auto& i : arr) cin >> i;

  SegTree tree(n, arr);

  int q;
  cin >> q;
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    cout << tree.query(--l, --r, k) << '\n';
  }

  return 0;
}
