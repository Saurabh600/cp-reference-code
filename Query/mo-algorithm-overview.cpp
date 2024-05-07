#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);

  ll n, t;
  cin >> n >> t;

  vector<ll> a(n);
  for (auto& i : a) cin >> i;
  vector<array<ll, 3>> query(t);

  ll l, r;
  for (int i = 0; i < t; i++) {
    cin >> l >> r;
    query[i] = {--l, --r, i};
  }

  ll B = sqrt(n) + 1;
  sort(query.begin(), query.end(), [B](auto& a, auto& b) {
    if (a[0] / B != b[0] / B) return a[0] / B < b[0] / B;
    return a[1] < b[1];
  });

  vector<ll> res(t);
  vector<ll> freq(int(1e6 + 10));
  ll ans = 0;

  auto add = [&](ll x) {
    ll it = a[x];
    ans -= freq[it] * freq[it] * it;
    freq[it]++;
    ans += freq[it] * freq[it] * it;
  };

  auto remove = [&](ll x) {
    ll it = a[x];
    ans -= freq[it] * freq[it] * it;
    freq[it]--;
    ans += freq[it] * freq[it] * it;
  };

  ll currL = 0, currR = -1;
  for (auto& q : query) {
    l = q[0], r = q[1];

    while (currL > l) currL--, add(currL);
    while (currR < r) currR++, add(currR);

    while (currL < l) remove(currL), currL++;
    while (currR > r) remove(currR), currR--;

    res[q[2]] = ans;
  }

  for (auto i : res) cout << i << '\n';

  return 0;
}
