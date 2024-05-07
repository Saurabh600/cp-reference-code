#include <bits/stdc++.h>
using namespace std;

class sparse_table {
  int n, LOG;
  vector<vector<int>> dp;

  public:
  template <class T>
  sparse_table(const T &arr) {
    n = arr.size();
    LOG = int(log2(n)) + 1;
    dp.resize(n, vector<int>(LOG));

    for (int i = 0; i < n; i++) dp[i][0] = arr[i];
    for (int k = 1; k < LOG; k++) {
      for (int i = 0; i + (1 << k) - 1 < n; i++) {
        dp[i][k] = min(dp[i][k - 1], dp[i + (1 << (k - 1))][k - 1]);
      }
    }
  }

  int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return min(dp[l][k], dp[r - (1 << k) + 1][k]);
  }
};

int main() {
  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (auto &i : arr) cin >> i;

  sparse_table st(arr);

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    cout << st.query(l, r) << '\n';
  }
  return 0;
}
