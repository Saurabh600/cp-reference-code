#include <bits/stdc++.h>
using namespace std;

template <class T>
class FenwickTree2D {
  public:
  std::vector<vector<T>> bit;
  int n, m;

  template <class M>
  FenwickTree2D(const std::vector<vector<M>>& v) {
    n = v.size();
    m = v[0].size();
    bit.resize(n + 1, vector<T>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= m; j++) {
        update(i, j, v[i - 1][j - 1]);
      }
    }
  }

  FenwickTree2D(int n, int m) {
    this->n = n;
    this->m = m;
    bit.resize(n + 1, vector<T>(m + 1, 0));
  }

  T get(int x, int y) {
    T sum = 0;
    for (int i = x; i > 0; i -= (i & -i)) {
      for (int j = y; j > 0; j -= (j & -j)) {
        sum += bit[i][j];
      }
    }
    return sum;
  }

  void update(int x, int y, int val) {
    for (int i = x; i <= n; i += (i & -i)) {
      for (int j = y; j <= m; j += (j & -j)) {
        bit[i][j] += val;
      }
    }
  }

  T get(int x1, int y1, int x2, int y2) {
    return get(x2, y2) - get(x2, y1 - 1) - get(x1 - 1, y2) + get(x1 - 1, y1 - 1);
  }
};
