#include <bits/stdc++.h>
using namespace std;

#define lc(i) (2 * i + 1)
#define rc(i) (2 * i + 2)

template <class T = int>
class seg_tree {
  public:
  template <class M>
  seg_tree(const M& arr, T _def, function<T(T, T)> fn) : n(arr.size()), def(_def), unite(fn) {
    tree.resize(n << 2);
    build(0, 0, n - 1, arr);
  }

  T query(T l, T r) { return query(0, 0, n - 1, l, r); }
  void update(T pos, T val) { update(0, 0, n - 1, pos, val); }

  private:
  T n, def;
  vector<T> tree;
  function<T(T, T)> unite;

  template <class M>
  void build(T i, T x, T y, const M& arr) {
    if (x == y) {
      tree[i] = arr[x];
    } else {
      T m = (x + y) >> 1;
      build(lc(i), x, m, arr);
      build(rc(i), m + 1, y, arr);
      tree[i] = unite(tree[lc(i)], tree[rc(i)]);
    }
  }

  T query(T i, T x, T y, T l, T r) {
    if (l > y || r < x || l > r) return def;
    if (l <= x && r >= y) return tree[i];
    T tm = (x + y) >> 1;
    return unite(query(lc(i), x, tm, l, r), query(rc(i), tm + 1, y, l, r));
  }

  void update(T i, T x, T y, T pos, T val) {
    if (x == y) {
      tree[i] = val;
    } else {
      T m = (x + y) >> 1;
      if (pos >= x && pos <= m) update(lc(i), x, m, pos, val);
      else update(rc(i), m + 1, y, pos, val);
      tree[i] = unite(tree[lc(i)], tree[rc(i)]);
    }
  }
};
