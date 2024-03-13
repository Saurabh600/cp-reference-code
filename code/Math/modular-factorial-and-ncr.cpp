#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 7;
const int64_t MOD = 1000000007;

vector<int64_t> fact, inv_fact;

int64_t mpow(int64_t base, int64_t exponent, int64_t modular = MOD) {
  base %= modular;
  int64_t result = 1;
  while (exponent > 0) {
    if (exponent & 1) result = (result * base) % modular;
    base = (base * base) % modular;
    exponent >>= 1;
  }

  return result;
}

int64_t add(int64_t n1, int64_t n2, int64_t modular = MOD) {
  return (n1 + n2) % modular;
}

int64_t subs(int64_t n1, int64_t n2, int64_t modular = MOD) {
  return ((n1 - n2) % modular + modular) % modular;
}

int64_t mul(int64_t n1, int64_t n2, int64_t modular = MOD) {
  return ((n1 % modular) * (n2 % modular)) % modular;
}

void build_factorial(int64_t n) {
  fact.resize(n);
  fact[0] = 1;
  for (int i = 1; i < n; i++) {
    fact[i] = (fact[i - 1] * i) % MOD;
  }
}

void build_inverse_factorial(int64_t n) {
  inv_fact.resize(n);
  inv_fact[0] = 1;
  for (int i = 1; i < n; i++) {
    inv_fact[i] = mpow(fact[i], MOD - 2, MOD);
  }
}

int64_t ncr(int64_t n, int64_t r) {
  if (r > n) return 0;
  return mul(mul(fact[n], inv_fact[r]), inv_fact[n - r]);
}

int main() {
  build_factorial(N);
  build_factorial(N);
  cout << ncr(25, 10) << "\n";
  return 0;
}
