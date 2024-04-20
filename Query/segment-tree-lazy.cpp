#include <bits/stdc++.h>
using namespace std;

template <class T = int>
class SegTree {
#define lc(i) 2 * i + 1
#define rc(i) 2 * i + 2

  T N, default_val;
  vector<T> tree;
  vector<T> lazy;

  template <class U>
  void buildTree(T v, T tl, T tr, vector<U>& A) {
    if (tl == tr) {
      tree[v] = A[tl];
    } else {
      T tm = (tl + tr) >> 1;
      buildTree(2 * v + 1, tl, tm, A);
      buildTree(2 * v + 2, tm + 1, tr, A);
      tree[v] = unite(tree[lc(v)], tree[rc(v)]);
    }
  }

  void applyLazyUpdates(T v, T tl, T tr) {
    if (lazy[v] != 0) {
      tree[v] += (tr - tl + 1) * lazy[v];
      if (tl != tr) {
        lazy[lc(v)] += lazy[v];
        lazy[rc(v)] += lazy[v];
      }
      lazy[v] = 0;
    }
  }

  void pushDown(T v, T tl, T tr, T val) {
    tree[v] += (tr - tl + 1) * val;
    if (tl != tr) {
      lazy[lc(v)] += val;
      lazy[rc(v)] += val;
    }
  }

  T query(T v, T tl, T tr, T l, T r) {
    applyLazyUpdates(v, tl, tr);
    if (l <= tl && r >= tr) return tree[v];
    if (l > tr || r < tl || l > r) return default_val;
    T tm = (tl + tr) >> 1;
    return unite(query(lc(v), tl, tm, l, r), query(rc(v), tm + 1, tr, l, r));
  }

  void rangeUpdate(T v, T tl, T tr, T l, T r, T val) {
    applyLazyUpdates(v, tl, tr);
    if (l > tr || r < tl || l > r) return;
    if (tl >= l && tr <= r) {
      pushDown(v, tl, tr, val);
      return;
    }
    T tm = (tl + tr) >> 1;
    rangeUpdate(lc(v), tl, tm, l, r, val);
    rangeUpdate(rc(v), tm + 1, tr, l, r, val);
    tree[v] = unite(tree[lc(v)], tree[rc(v)]);
  }

  T unite(T a, T b) { return min(a, b); }

  public:
  template <class U>
  SegTree(vector<U> A, T default_val = 0) : N(A.size()), default_val(default_val) {
    tree.resize(4 * N);
    lazy.resize(4 * N);
    buildTree(0, 0, N - 1, A);
  }

  T query(T l, T r) { return query(0, 0, N - 1, l, r); }
  void rangeUpdate(T l, T r, T val) { rangeUpdate(0, 0, N - 1, l, r, val); }
};
