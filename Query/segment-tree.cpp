#include <bits/stdc++.h>
using namespace std;

template <class T = int>
class SegTree {
#define lc(i) 2 * i + 1
#define rc(i) 2 * i + 2

  T N, default_val;
  vector<T> tree;
  function<T(T, T)> unite;

  template <class M>
  void buildTree(T v, T tl, T tr, vector<M>& A) {
    if (tl == tr) {
      tree[v] = A[tl];
    } else {
      T tm = (tl + tr) >> 1;
      buildTree(lc(v), tl, tm, A);
      buildTree(rc(v), tm + 1, tr, A);
      tree[v] = unite(tree[lc(v)], tree[rc(v)]);
    }
  }

  T query(T v, T tl, T tr, T l, T r) {
    if (l <= tl && r >= tr) return tree[v];
    if (l > tr || r < tl || l > r) return default_val;

    T tm = (tl + tr) >> 1;
    return unite(query(lc(v), tl, tm, l, r), query(rc(v), tm + 1, tr, l, r));
  }

  void update(T v, T tl, T tr, T pos, T new_val) {
    if (tl == tr) {
      tree[v] = new_val;
    } else {
      T tm = (tl + tr) >> 1;
      if (pos >= tl && pos <= tm) update(lc(v), tl, tm, pos, new_val);
      else update(rc(v), tm + 1, tr, pos, new_val);
      tree[v] = unite(tree[lc(v)], tree[rc(v)]);
    }
  }

  public:
  template <class M>
  SegTree(vector<M> A, T default_val = 0, function<T(T, T)> unite_fn = plus<T>())
      : N(A.size()), default_val(default_val), unite(unite_fn) {
    tree.resize(4 * N);
    buildTree(0, 0, N - 1, A);
  }

  T query(T l, T r) { return query(0, 0, N - 1, l, r); }
  void update(T pos, T new_val) { update(0, 0, N - 1, pos, new_val); }
};
