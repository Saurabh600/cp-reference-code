#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
  private:
  vector<int64_t> arr;
  vector<int64_t> seg;
  vector<int64_t> lazy;
  int N;

  void _build_seg(int node, int ss, int se) {
    if (ss == se) {
      seg[node] = arr[ss];
      return;
    }

    int mid = (ss + se) >> 1;
    _build_seg(2 * node + 1, ss, mid);
    _build_seg(2 * node + 2, mid + 1, se);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
  }

  int64_t _query(int node, int ss, int se, int qs, int qe) {
    if (lazy[node] != 0) {
      seg[node] += (se - ss + 1) * lazy[node];
      if (ss != se) {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
      }
      lazy[node] = 0;
    }

    if (qe < ss || qs > se) return 0;
    if (ss >= qs && se <= qe) return seg[node];

    int mid = (ss + se) >> 1;
    int64_t left = _query(2 * node + 1, ss, mid, qs, qe);
    int64_t right = _query(2 * node + 2, mid + 1, se, qs, qe);
    return left + right;
  }

  void _range_update(int node, int ss, int se, int qs, int qe, int val) {
    if (lazy[node] != 0) {
      seg[node] += (se - ss + 1) * lazy[node];
      if (ss != se) {
        lazy[2 * node + 1] += lazy[node];
        lazy[2 * node + 2] += lazy[node];
      }
      lazy[node] = 0;
    }

    if (qs > se || qe < ss || qs > qe) return;
    if (ss >= qs && se <= qe) {
      seg[node] += (se - ss + 1) * val;
      if (ss != se) {
        lazy[2 * node + 1] += val;
        lazy[2 * node + 2] += val;
      }
      return;
    }

    int mid = (ss + se) >> 1;
    _range_update(2 * node + 1, ss, mid, qs, qe, val);
    _range_update(2 * node + 2, mid + 1, se, qs, qe, val);
    seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
  }

  public:
  SegmentTree(vector<int64_t>& vec) {
    this->arr = vec;
    this->N = int(vec.size());
    seg.assign(4 * N, 0);
    lazy.assign(4 * N, 0);
    _build_seg(0, 0, N - 1);
  }
  int64_t query(int qs, int qe) {
    return _query(0, 0, N - 1, qs, qe);
  }
  void range_update(int qs, int qe, int val) {
    _range_update(0, 0, N - 1, qs, qe, val);
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
    int t;
    cin >> t;
    if (t == 1) {
      int a, b, u;
      cin >> a >> b >> u;
      a--, b--;
      seg.range_update(a, b, u);
    } else {
      int k;
      cin >> k;
      k--;
      cout << seg.query(k, k) << '\n';
    }
  }
  return 0;
}
