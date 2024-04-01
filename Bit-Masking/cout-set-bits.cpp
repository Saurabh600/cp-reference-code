#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll count_set_bits_itr(ll n) {
  ll result = 0, x = 0;
  while (n > 1) {
    x = 63 - __builtin_clzll(n);
    n &= ~(1LL << x);
    result += (1LL << (x - 1)) * x;
    result += n + 1;
  }
  result += n;
  return result;
}

ll count_set_bits_recursive(ll n) {
  if (n < 2) return n;

  int x = 63 - __builtin_clzll(n);

  ll bits_till_2x = x * (1LL << (x - 1));  // (2^x)/2 * x == (2^(x-1))*x
  ll bits_from_2x = n - (1LL << x) + 1;    // n - (2^x) + 1 i.e last bit
  ll rest = n & (~(1LL << x));             // from 2^x to n without last set bit
  return bits_till_2x + bits_from_2x + count_set_bits_recursive(rest);
}

int main() {
  ll n;
  cin >> n;
  cout << "recursive: " << count_set_bits_recursive(n) << '\n';
  cout << "itr: " << count_set_bits_itr(n) << '\n';
  return 0;
}
