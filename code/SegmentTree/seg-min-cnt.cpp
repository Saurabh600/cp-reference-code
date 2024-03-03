#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

template <class T>
class SegmentTree {
  private:
  struct seg_node {
    T mn, cnt;
    seg_node(T x) {
      this->mn = x;
      cnt = 1;
    }

    seg_node() {
      this->mn = inf;
      this->cnt = 0;
    }

    seg_node(seg_node& n1, seg_node& n2) {
      if (n1.mn == n2.mn) {
        this->mn = n1.mn;
        this->cnt = n1.cnt + n2.cnt;
      } else {
        if (n1.mn < n2.mn) {
          this->mn = n1.mn;
          this->cnt = n1.cnt;
        } else {
          this->mn = n2.mn;
          this->cnt = n2.cnt;
        }
      }
    }
  };
  vector<seg_node> arr;
  vector<seg_node> seg;
  int len;

  void _build_seg(int node, int ss, int se) {
    if (ss == se) {
      seg[node] = seg_node(arr[ss]);
      return;
    }

    int mid = (ss + se) >> 1;
    _build_seg(2 * node + 1, ss, mid);
    _build_seg(2 * node + 2, mid + 1, se);
    seg[node] = seg_node(seg[2 * node + 1], seg[2 * node + 2]);
  }

  seg_node _query(int node, int ss, int se, int qs, int qe) {
    if (ss >= qs && se <= qe) return seg[node];
    if (qe < ss || qs > se) return seg_node();

    int mid = (ss + se) >> 1;
    auto left = _query(2 * node + 1, ss, mid, qs, qe);
    auto right = _query(2 * node + 2, mid + 1, se, qs, qe);
    return seg_node(left, right);
  }

  void _update(int node, int ss, int se, int idx, int val) {
    if (ss == se) {
      arr[idx] = val;
      seg[node] = seg_node(arr[idx]);
      return;
    }

    int mid = (ss + se) >> 1;
    if (idx >= ss && idx <= mid) _update(2 * node + 1, ss, mid, idx, val);
    else _update(2 * node + 2, mid + 1, se, idx, val);
    seg[node] = seg_node(seg[2 * node + 1], seg[2 * node + 2]);
  }

  public:
  SegmentTree(vector<T>& vec) {
    this->len = int(vec.size());
    this->arr.resize(this->len);
    for (int i = 0; i < len; i++) arr[i] = seg_node(vec[i]);
    seg.resize(4 * len);
    _build_seg(0, 0, len - 1);
  }

  seg_node query(int qs, int qe) {
    return _query(0, 0, len - 1, qs, qe);
  }

  void update(int idx, int val) {
    _update(0, 0, len - 1, idx, val);
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<long long> a(n);
  for (auto& i : a) cin >> i;
  SegmentTree<long long> seg(a);
  while (q--) {
    int t;
    cin >> t;
    if (t != 1) {
      int a, b;
      cin >> a >> b;
      b--;
      auto [mn, cnt] = seg.query(a, b);
      cout << mn << ' ' << cnt << '\n';
    } else {
      int k, u;
      cin >> k >> u;
      seg.update(k, u);
    }
  }
  return 0;
}
