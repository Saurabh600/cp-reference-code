#include <bits/stdc++.h>
using namespace std;

int main() {
  int N = 1e7 + 7;
  vector<int> prime(N, 1);
  vector<int> lp(N, 0), hp(N, 0);

  // calculating primes till N
  prime[0] = prime[1] = 0;
  for (int i = 2; i < N; i++) {
    if (!prime[i]) continue;
    hp[i] = lp[i] = i;
    for (int j = 2 * i; j < N; j += i) {
      prime[j] = 0;
      hp[j] = i;
      if (!lp[j]) lp[j] = i;
    }
  }

  // calculating all divisors till N
  N = 1e5;
  vector<int> divisors[N];
  for (int i = 1; i < N; i++) {
    for (int j = i; j < N; j += i) {
      divisors[j].push_back(i);
    }
  }

  for (int f : divisors[53900]) cout << f << ' ';
  cout << '\n';

  // calculating prime factors using highest prime
  // TC: O(log(N))
  int num = 1185800;
  map<int, int> mp;
  while (num > 1) {
    int fact = hp[num];
    while (num % fact == 0) {
      num /= fact;
      mp[fact]++;
    }
  }

  return 0;
}