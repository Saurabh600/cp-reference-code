#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5 + 5;
const int LOG = 20;
int m[MAXN][LOG];
int bin_log[MAXN];

int query(int l, int r) {
  int len = r - l + 1;
  // int k = bin_log[len];
  int k = 31 - __builtin_clz(len);
  return min(m[l][k], m[r - (1 << k) + 1][k]);
}

void preprocess(int arr[], int n) {
  bin_log[1] = 0;
  for (int i = 2; i <= n; i++) bin_log[i] = bin_log[i / 2] + 1;
  for (int i = 1; i <= n; i++) m[i][0] = arr[i];

  for (int k = 1; k < LOG; k++) {
    for (int i = 1; i + (1 << k) - 1 <= n; i++) {
      m[i][k] = min(m[i][k - 1], m[i + (1 << (k - 1))][k - 1]);
    }
  }
}

int main() {
  int n, q;
  cin >> n >> q;
  int arr[n + 1];
  for (int i = 1; i <= n; i++) cin >> arr[i];

  preprocess(arr, n);

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << query(l, r) << '\n';
  }
  return 0;
}
