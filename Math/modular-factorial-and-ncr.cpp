#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;

long long add(long long a, long long b, long long p) { return ((a + b) % p + p) % p; }
long long mul(long long a, long long b, long long p) { return ((a % p) * (b % p)) % p; }
long long binexp(long long a, long long e, long long p) {
  long long res = 1;
  for (; e > 0; e >>= 1, a = a * a % p) {
    if (e & 1) res = res * a % p;
  }
  return res;
}

vector<int> fact, inv_fact;

void preprocess(int N, int p) {
  fact.resize(N + 1);
  fact[0] = 1;
  for (int i = 1; i <= N; i++) {
    fact[i] = 1LL * fact[i - 1] * i % p;
  }

  inv_fact.resize(N + 1);
  inv_fact[N] = binexp(fact[N], p - 2, p);
  for (int i = N - 1; i >= 0; i--) {
    inv_fact[i] = 1LL * (i + 1) * inv_fact[i + 1] % p;
  }
}

int ncr(int n, int r) {
  if (r > n) return 0;
  int ans = mul(fact[n], inv_fact[r], MOD);
  ans = mul(ans, inv_fact[n - r], MOD);
  return ans;
}

int main() {
  preprocess(1e6, MOD);
  cout << ncr(25, 10) << "\n";
  return 0;
}
