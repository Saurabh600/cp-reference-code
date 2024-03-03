#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  private:
  vector<int64_t> arr;
  vector<int64_t> seg;
  int len;

  void _build_seg(int node, int ss, int se) {
    if (ss == se) {
      seg[node] = arr[ss];
      return;
    }

    int mid = (ss + se) >> 1;
    _build_seg(2 * node + 1, ss, mid);
    _build_seg(2 * node + 2, mid + 1, se);
    seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
  }

  int64_t _query(int node, int ss, int se, int qs, int qe) {
    if (ss >= qs && se <= qe) return seg[node];
    if (qe < ss || qs > se) return 0;

    int mid = (ss + se) >> 1;
    int64_t left = _query(2 * node + 1, ss, mid, qs, qe);
    int64_t right = _query(2 * node + 2, mid + 1, se, qs, qe);
    return left ^ right;
  }

  void _update(int node, int ss, int se, int idx, int val) {
    if (ss == se) {
      arr[idx] += val;
      seg[node] += val;
      return;
    }

    int mid = (ss + se) >> 1;
    if (idx >= ss && idx <= mid) _update(2 * node + 1, ss, mid, idx, val);
    else _update(2 * node + 2, mid + 1, se, idx, val);
    seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
  }

  public:
  SegmentTree(vector<int64_t>& vec) {
    this->arr = vec;
    this->len = int(vec.size());
    seg.resize(4 * len);
    _build_seg(0, 0, len - 1);
  }

  int64_t query(int qs, int qe) {
    return _query(0, 0, len - 1, qs, qe);
  }

  void update(int idx, int val) {
    _update(0, 0, len - 1, idx, val);
  }
};

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  int n, q;
  cin >> n >> q;
  vector<int64_t> vec(n);
  for (int i = 0; i < n; i++) cin >> vec[i];
  SegmentTree seg(vec);
  while (q--) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    cout << seg.query(a, b) << '\n';
  }
  return 0;
}
