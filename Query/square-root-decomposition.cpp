#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 1e6;
const int MAXB = 1e3;

ll arr[MAXN];
ll block[MAXB];
int B;

void preprocess(int n) {
  B = sqrt(n);
  int idx = -1;
  for (int i = 0; i < n; i++) {
    if (i % B == 0) idx++;
    block[idx] += arr[i];
  }
}

void update(int idx, ll val) {
  block[idx / B] += val - arr[idx];
  arr[idx] = val;
}

ll query(int l, int r) {
  ll sum = 0;
  while (l < r && l % B != 0) sum += arr[l], l++;
  while (l + B - 1 <= r) sum += block[l / B], l += B;
  while (l <= r) sum += arr[l], l++;
  return sum;
}
