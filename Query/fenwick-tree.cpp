#include <bits/stdc++.h>
using namespace std;

template <class T = int>
struct BIT {
  T N;
  vector<T> bit;

  BIT(T n) : N(n + 1) { bit.assign(N, 0); }

  template <class U>
  BIT(T n, U& A) : BIT(n) {
    for (T i = 1; i < N; i++) {
      bit[i] += A[i - 1];
      T rsb = i & -i;
      if (i + rsb < N) bit[i + rsb] += bit[i];
    }
  }

  T query(T i) {
    T sum = 0;
    for (; i > 0; i -= i & -i) sum += bit[i];
    return sum;
  }

  void update(T i, T val) {
    assert(i > 0);
    for (; i < N; i += i & -i) bit[i] += val;
  }

  T query(T l, T r) { return query(r) - query(l - 1); }
};
