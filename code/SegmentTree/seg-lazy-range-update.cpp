#include <bits/stdc++.h>
using namespace std;

class SegTreeLazy {
    private:
    vector<int64_t> arr;
    vector<int64_t> seg;
    vector<int64_t> lazy;
    int N;

    void build(int i, int x, int y) {
        if (x == y) {
            seg[i] = arr[x];
        } else {
            int m = (x + y) >> 1;
            build(2 * i + 1, x, m);
            build(2 * i + 2, m + 1, y);
            seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
        }
    }

    int64_t query(int i, int x, int y, int l, int r) {
        if (lazy[i] != 0) {
            seg[i] += (y - x + 1) * lazy[i];
            if (x != y) {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }

        if (r < x || l > y) return 0;
        if (x >= l && y <= r) return seg[i];

        int m = (x + y) >> 1;
        int64_t left = query(2 * i + 1, x, m, l, r);
        int64_t right = query(2 * i + 2, m + 1, y, l, r);
        return left + right;
    }

    void range_update(int i, int x, int y, int l, int r, int val) {
        if (lazy[i] != 0) {
            seg[i] += (y - x + 1) * lazy[i];
            if (x != y) {
                lazy[2 * i + 1] += lazy[i];
                lazy[2 * i + 2] += lazy[i];
            }
            lazy[i] = 0;
        }

        if (l > y || r < x || l > r) return;

        if (x >= l && y <= r) {
            seg[i] += (y - x + 1) * val;
            if (x != y) {
                lazy[2 * i + 1] += val;
                lazy[2 * i + 2] += val;
            }
        } else {
            int m = (x + y) >> 1;
            range_update(2 * i + 1, x, m, l, r, val);
            range_update(2 * i + 2, m + 1, y, l, r, val);
            seg[i] = seg[2 * i + 1] + seg[2 * i + 2];
        }
    }

    public:
    SegTreeLazy(vector<int64_t>& vec) {
        this->arr = vec;
        this->N = int(vec.size());
        seg.assign(4 * N, 0);
        lazy.assign(4 * N, 0);
        build(0, 0, N - 1);
    }
    int64_t query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }
    void range_update(int l, int r, int val) {
        range_update(0, 0, N - 1, l, r, val);
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int64_t> vec(n);
    for (int i = 0; i < n; i++) cin >> vec[i];
    SegTreeLazy seg(vec);
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b, u;
            cin >> a >> b >> u;
            seg.range_update(a - 1, b - 1, u);
        } else {
            int k;
            cin >> k;
            cout << seg.query(k - 1, k - 1) << '\n';
        }
    }
    return 0;
}
