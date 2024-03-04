#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

struct seg_node {
    int64_t min_val, max_val, sum_val;
    seg_node(int64_t x) {
        this->min_val = x;
        this->max_val = x;
        this->sum_val = x;
    }

    seg_node() {
        this->min_val = inf;
        this->max_val = -inf;
        this->sum_val = 0;
    }

    seg_node(seg_node& n1, seg_node& n2) {
        this->min_val = min(n1.min_val, n2.min_val);
        this->max_val = max(n1.max_val, n2.max_val);
        this->sum_val = n1.sum_val + n2.sum_val;
    }
};

class SegTree {
    private:
    vector<seg_node> arr;
    vector<seg_node> seg;
    int N;

    void _build_seg(int i, int x, int y) {
        if (x == y) {
            seg[i] = seg_node(arr[x]);
        } else {
            int m = (x + y) >> 1;
            _build_seg(2 * i + 1, x, m);
            _build_seg(2 * i + 2, m + 1, y);
            seg[i] = seg_node(seg[2 * i + 1], seg[2 * i + 2]);
        }
    }

    seg_node query(int i, int x, int y, int l, int r) {
        if (x >= l && y <= r) return seg[i];
        if (r < x || l > y) return seg_node();

        int m = (x + y) >> 1;
        auto left = query(2 * i + 1, x, m, l, r);
        auto right = query(2 * i + 2, m + 1, y, l, r);
        return seg_node(left, right);
    }

    void update(int i, int x, int y, int node, int val) {
        if (x == y) {
            arr[node] = val;
            seg[i] = seg_node(arr[node]);
        } else {
            int m = (x + y) >> 1;
            if (node >= x && node <= m) update(2 * i + 1, x, m, node, val);
            else update(2 * i + 2, m + 1, y, node, val);
            seg[i] = seg_node(seg[2 * i + 1], seg[2 * i + 2]);
        }
    }

    public:
    SegTree(vector<int64_t>& vec) {
        this->N = int(vec.size());
        this->arr.resize(this->N);
        for (int i = 0; i < N; i++) arr[i] = seg_node(vec[i]);
        seg.resize(4 * N);
        _build_seg(0, 0, N - 1);
    }

    seg_node query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    void update(int node, int val) {
        update(0, 0, N - 1, node, val);
    }
};

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for (auto& i : a) cin >> i;
    SegTree seg(a);
    while (q--) {
        int t;
        cin >> t;
        if (t != 1) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            cout << seg.query(a, b).min_val << '\n';
        } else {
            int k, u;
            cin >> k >> u;
            k--;
            seg.update(k, u);
        }
    }
    return 0;
}
