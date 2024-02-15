#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;

const ll N = 200005;
const ll INF = 1e18;

ll A[N];
ll seg[4 * N];

void build_tree(ll idx, ll low, ll high) {
    if (low == high) {
        seg[idx] = A[low];
        return;
    }

    ll mid = (low + high) >> 1;
    build_tree(2 * idx + 1, low, mid);
    build_tree(2 * idx + 2, mid + 1, high);
    seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
}

ll query(ll idx, ll low, ll high, ll l, ll r) {
    if (l <= low && r >= high) return seg[idx];
    if (l > high || r < low) return INF;

    ll mid = (low + high) >> 1;
    ll left = query(2 * idx + 1, low, mid, l, r);
    ll right = query(2 * idx + 2, mid + 1, high, l, r);
    return min(left, right);
}

void update(ll idx, ll low, ll high, ll node, ll val) {
    if (low == high) {
        seg[idx] = val;
    } else {
        ll mid = (low + high) >> 1;
        if (node >= low && node <= mid)
            update(2 * idx + 1, low, mid, node, val);
        else update(2 * idx + 2, mid + 1, high, node, val);

        seg[idx] = min(seg[2 * idx + 1], seg[2 * idx + 2]);
    }
}
