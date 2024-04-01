#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

const ll N = 1e6;
const ll M = 1e3;

ll arr[N];
ll block[M];
ll blk_size;

void preprocess(ll n) {
    blk_size = sqrt(n);
    ll idx = -1;
    for (ll i = 0; i < n; i++) {
        if (i % blk_size == 0) idx++;
        block[idx] += arr[i];
    }
}

void update(ll idx, ll val) {
    ll blk_idx = idx / blk_size;
    block[blk_idx] += val - arr[idx];
    arr[idx] = val;
}

ll query(ll l, ll r) {
    ll sum = 0;

    while (l < r && l % blk_size != 0) {
        sum += arr[l];
        l++;
    }

    while (l + blk_size - 1 <= r) {
        sum += block[l / blk_size];
        l += blk_size;
    }

    while (l <= r) {
        sum += arr[l];
        l++;
    }

    return sum;
}
