#include <bits/stdc++.h>
using namespace std;

#define lc(i) 2 * i + 1
#define rc(i) 2 * i + 2

template <class T = int>
class SegTree {
  T n, def;
  vector<T> tree;
  vector<T> lazy;

  template <class U>
  void build(T i, T x, T y, const vector<U>& arr) {
    if (x == y) {
      tree[i] = arr[x];
    } else {
      T m = (x + y) >> 1;
      build(lc(i), x, m, arr);
      build(rc(i), m + 1, y, arr);
      tree[i] = unite(tree[lc(i)], tree[rc(i)]);
    }
  }

  void apply_lazy(T i, T x, T y) {
    if (lazy[i] != 0) {
      tree[i] += (y - x + 1) * lazy[i];
      if (x != y) {
        lazy[lc(i)] += lazy[i];
        lazy[rc(i)] += lazy[i];
      }
      lazy[i] = 0;
    }
  }

  void push(T i, T x, T y, T val) {
    tree[i] += (y - x + 1) * val;
    if (x != y) {
      lazy[lc(i)] += val;
      lazy[rc(i)] += val;
    }
  }

  T query(T i, T x, T y, T l, T r) {
    apply_lazy(i, x, y);
    if (l <= x && r >= y) return tree[i];
    if (l > y || r < x || l > r) return def;
    T tm = (x + y) >> 1;
    return unite(query(lc(i), x, tm, l, r), query(rc(i), tm + 1, y, l, r));
  }

  void range_update(T i, T x, T y, T l, T r, T val) {
    apply_lazy(i, x, y);
    if (l > y || r < x || l > r) return;
    if (x >= l && y <= r) {
      push(i, x, y, val);
      return;
    }
    T m = (x + y) >> 1;
    range_update(lc(i), x, m, l, r, val);
    range_update(rc(i), m + 1, y, l, r, val);
    tree[i] = unite(tree[lc(i)], tree[rc(i)]);
  }

  T unite(T a, T b) { return min(a, b); }

  public:
  template <class U>
  SegTree(const vector<U>& arr, T _def = 0) : n(arr.size()), def(_def) {
    tree.resize(n << 2);
    lazy.resize(n << 2);
    build(0, 0, n - 1, arr);
  }

  T query(T l, T r) { return query(0, 0, n - 1, l, r); }
  void rangeUpdate(T l, T r, T val) { range_update(0, 0, n - 1, l, r, val); }
};
