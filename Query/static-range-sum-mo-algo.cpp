/**
  author: Saurabh Chaudhary (Saurabh600)
  created: 11.04.2024 17:39:35
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#ifdef LOCAL_RUN
#include "debug.h"
#else
#define debug(...) 42
#endif

signed main() {
  ios_base::sync_with_stdio(0), cin.tie(0);

  int n, q;
  cin >> n >> q;
  vector<int> arr(n);
  for (auto& i : arr) cin >> i;

  vector<vector<int>> query(q);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    query[i] = vector<int>{--l, --r, i};
  }

  int B = sqrt(n);
  sort(query.begin(), query.end(), [B](auto& q1, auto& q2) {
    auto l1 = q1[0], r1 = q1[1];
    auto l2 = q2[0], r2 = q2[1];

    if (l1 / B != l2 / B) return l1 / B < l2 / B;
    return r1 < r2;
  });

  int currL = 0, currR = 0;
  long long sum = 0;
  vector<long long> ans(q);
  for (auto& it : query) {
    auto L = it[0], R = it[1], ind = it[2];

    while (currL < L) sum -= arr[currL++];
    while (currL > L) sum += arr[--currL];

    while (currR < R + 1) sum += arr[currR++];
    while (currR > R + 1) sum -= arr[--currR];

    ans[ind] = sum;
  }

  for (auto v : ans) cout << v << '\n';

  return 0;
}
