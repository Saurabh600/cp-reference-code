/**
   author: Saurabh Chaudhary
   created: 2024-05-19 21:15:38
*/
#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include "algo/debug.h"
#else
#define debug(...) 42
#endif

typedef long long ll;
typedef long double ld;

struct Query {
  int l;
  int r;
  int ind;
};

struct Cmp {
  int block_size;
  Cmp(int _block_size) : block_size(_block_size) {
  }
  bool operator()(const Query& q1, const Query& q2) {
    auto l1 = q1.l, r1 = q1.r;
    auto l2 = q2.l, r2 = q2.r;
    return (l1 / block_size != l2 / block_size)
               ? (l1 / block_size < l2 / block_size)
               : (r1 < r2);
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (auto& i : a) cin >> i;

  vector<Query> queries(q);
  for (int i = 0, l, r; i < q; i++) {
    cin >> l >> r;
    queries[i] = {--l, --r, i};
  }

  sort(queries.begin(), queries.end(), Cmp(sqrt(n) + 1));

  ll curr_ans = 0;
  auto add = [&](int i) { curr_ans += a[i]; };
  auto rem = [&](int i) { curr_ans -= a[i]; };

  vector<ll> res(q);
  int currL = 0, currR = -1;
  for (auto [l, r, ind] : queries) {
    while (currL > l) currL--, add(currL);
    while (currR < r) currR++, add(currR);

    while (currL < l) rem(currL), currL++;
    while (currR > r) rem(currR), currR--;

    res[ind] = curr_ans;
  }

  for (auto i : res) cout << i << "\n";

  return 0;
}
