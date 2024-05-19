#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

inline ll add(ll a, ll b, ll m) { return ((a % m) + (b % m) + m) % m; }
inline ll mul(ll a, ll b, ll m) { return ((a % m) * (b % m)) % m; }
inline ll norm(ll a, ll m) { return (a % m + m) % m; }
inline ll binexp(ll a, ll e, ll m) {
  ll res = 1;
  for (a %= m; e > 0; e >>= 1, a = a * a % m)
    if (e & 1) res = res * a % m;
  return res;
}
inline ll inv(ll a, ll m) { return binexp(a, m - 2, m); }
inline ll mul(const vector<ll>& v, ll m) {
  ll res = 1;
  for (auto it : v) res = mul(res, it, m);
  return res;
}
inline ll add(const vector<ll>& v, ll m) {
  ll res = 0;
  for (auto it : v) res = add(res, it, m);
  return res;
}

vector<ll> fact, inv_fact;
void gen_fact(ll _n, ll m) {
  fact.resize(_n + 1);
  inv_fact.resize(_n + 1);

  // generating factorial
  fact[0] = 1;
  for (ll i = 1; i <= _n; i++) fact[i] = fact[i - 1] * i % m;

  // generating inverse factorial
  inv_fact[_n] = inv(fact[_n], m);
  for (ll i = _n - 1; i >= 0; i--) inv_fact[i] = inv_fact[i + 1] * (i + 1) % m;
}

inline ll ncr(ll n, ll r, ll m) {
  if (n < r) return 0;
  return mul({fact[n], inv(fact[r], m), inv(fact[n - r], m)}, m);
}

vector<ll> prime, hp, lp;
void sieve(int _n) {
  prime.assign(_n + 1, 1);
  lp.resize(_n + 1);
  hp.resize(_n + 1);
  prime[0] = prime[1] = 0;
  for (int i = 2; i <= _n; i++) {
    if (prime[i]) {
      hp[i] = lp[i] = i;
      for (int j = 2 * i; j <= _n; j += i) {
        prime[j] = 0;
        hp[j] = i;
        if (!lp[j]) lp[j] = i;
      }
    }
  }
}
