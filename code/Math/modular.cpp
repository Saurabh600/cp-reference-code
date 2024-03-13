#include <bits/stdc++.h>
using namespace std;

const int64_t MOD = 1000000007;

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
