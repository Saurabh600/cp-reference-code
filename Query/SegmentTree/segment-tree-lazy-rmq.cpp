#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

const ll N = 200005;

ll arr[N] = {};
ll seg[4 * N] = {};
ll lazy[4 * N] = {};

void build_tree(ll idx, ll low, ll high) {
    if (low == high) {
        seg[idx] = arr[low];
        return;
    }

    ll mid = (low + high) >> 1;
    build_tree(2 * idx + 1, low, mid);
    build_tree(2 * idx + 2, mid + 1, high);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}

ll query(ll idx, ll low, ll high, ll l, ll r) {
    if (lazy[idx] != 0) {
        seg[idx] += (high - low + 1) * lazy[idx];
        if (low != high) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    if (l <= low && r >= high) return seg[idx];
    if (l > high || r < low) return 0;

    ll mid = (low + high) >> 1;
    ll left = query(2 * idx + 1, low, mid, l, r);
    ll right = query(2 * idx + 2, mid + 1, high, l, r);
    return left + right;
}

void range_update(ll idx, ll low, ll high, ll l, ll r, ll val) {
    if (lazy[idx] != 0) {
        seg[idx] += (high - low + 1) * lazy[idx];
        if (low != high) {
            lazy[2 * idx + 1] += lazy[idx];
            lazy[2 * idx + 2] += lazy[idx];
        }
        lazy[idx] = 0;
    }

    if (l > high || r < low || low > high) return;
    if (low >= l && high <= r) {
        seg[idx] += (high - low + 1) * val;
        if (low != high) {
            lazy[2 * idx + 1] += val;
            lazy[2 * idx + 2] += val;
        }
        return;
    }

    ll mid = (low + high) >> 1;
    range_update(2 * idx + 1, low, mid, l, r, val);
    range_update(2 * idx + 2, mid + 1, high, l, r, val);
    seg[idx] = seg[2 * idx + 1] + seg[2 * idx + 2];
}
