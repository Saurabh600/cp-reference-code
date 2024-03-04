#include <bits/stdc++.h>
using namespace std;

class SegTree {
    private:
    vector<int64_t> arr;
    vector<int64_t> seg;
    int N;

    void build(int node, int x, int y) {
        if (x == y) {
            seg[node] = arr[x];
        } else {
            int m = (x + y) >> 1;
            build(2 * node + 1, x, m);
            build(2 * node + 2, m + 1, y);
            seg[node] = seg[2 * node + 1] + seg[2 * node + 2];
        }
    }

    int64_t query(int node, int x, int y, int l, int r) {
        if (x >= l && y <= r) return seg[node];
        if (r < x || l > y) return 0;

        int m = (x + y) >> 1;
        int64_t left = query(2 * node + 1, x, m, l, r);
        int64_t right = query(2 * node + 2, m + 1, y, l, r);
        return left + right;
    }

    void update(int node, int x, int y, int idx, int val) {
        if (x == y) {
            arr[idx] += val;
            seg[node] += val;
        } else {
            int m = (x + y) >> 1;
            if (idx >= x && idx <= m) update(2 * node + 1, x, m, idx, val);
            else update(2 * node + 2, m + 1, y, idx, val);
            seg[node] = seg[2 * node + 1] ^ seg[2 * node + 2];
        }
    }

    public:
    SegTree(vector<int64_t>& vec) {
        this->arr = vec;
        this->N = int(vec.size());
        seg.resize(4 * N);
        build(0, 0, N - 1);
    }

    int64_t query(int qs, int qe) {
        return query(0, 0, N - 1, qs, qe);
    }

    void update(int idx, int val) {
        update(0, 0, N - 1, idx, val);
    }
};

int main() {
    ios::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int64_t> vec(n);
    for (int i = 0; i < n; i++) cin >> vec[i];
    SegTree seg(vec);
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << seg.query(a - 1, b - 1) << '\n';
    }
    return 0;
}
