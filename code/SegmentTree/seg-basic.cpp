#include <bits/stdc++.h>
using namespace std;

class SegTree {
    private:
    vector<int64_t> arr;
    vector<int64_t> seg;
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
        if (x >= l && y <= r) return seg[i];
        if (r < x || l > y) return 0;

        int m = (x + y) >> 1;
        int64_t left = query(2 * i + 1, x, m, l, r);
        int64_t right = query(2 * i + 2, m + 1, y, l, r);
        return left + right;
    }

    void update(int i, int x, int y, int node, int val) {
        if (x == y) {
            arr[node] += val;
            seg[i] += val;
        } else {
            int m = (x + y) >> 1;
            if (node >= x && node <= m) update(2 * i + 1, x, m, node, val);
            else update(2 * i + 2, m + 1, y, node, val);
            seg[i] = seg[2 * i + 1] ^ seg[2 * i + 2];
        }
    }

    public:
    SegTree(vector<int64_t>& vec) {
        this->arr = vec;
        this->N = int(vec.size());
        seg.resize(4 * N);
        build(0, 0, N - 1);
    }

    int64_t query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    void update(int node, int val) {
        update(0, 0, N - 1, node, val);
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
