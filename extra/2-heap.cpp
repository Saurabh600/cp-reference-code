/**
   author: Saurabh Chaudhary
   created: 2024-05-15 20:28:20
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

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll n, q;
  cin >> n >> q;
  vector<ll> arr(n);
  for (auto& it : arr) cin >> it;

  /**
   * h1 : need lb(n/2) element
   * h2 : need ub(n/2)
   */
  priority_queue<ll> h1;
  priority_queue<ll, vector<ll>, greater<>> h2;

  ll s1 = 0, s2 = 0;
  vector<ll> res(n + 1);

  for (int i = 1; i <= n; i++) {
    auto it = arr[i - 1];

    if (h1.empty() || it <= h1.top()) h1.push(it), s1 += it;
    else h2.push(it), s2 += it;

    // balancing
    if (!h1.empty()) {
      h2.push(h1.top());
      s1 -= h1.top(), s2 += h1.top();
      h1.pop();
    }

    while (int(h1.size()) > i / 2) {
      h2.push(h1.top());
      s1 -= h1.top(), s2 += h1.top();
      h1.pop();
    }

    while (int(h1.size()) < i / 2) {
      h1.push(h2.top());
      s1 += h2.top(), s2 -= h2.top();
      h2.pop();
    }

    res[i] = s2 - s1;
  }

  return 0;
}
