#include <bits/stdc++.h>
using namespace std;

const long long inf = 1e18;

struct seg_node {
    int64_t mn, cnt;
    seg_node(int64_t x) {
        mn = x;
        cnt = 1;
    }

    seg_node() {
        mn = inf;
        cnt = 0;
    }

    seg_node(seg_node& n1, seg_node& n2) {
        if (n1.mn == n2.mn) {
            mn = n1.mn;
            cnt = n1.cnt + n2.cnt;
        } else {
            if (n1.mn < n2.mn) {
                mn = n1.mn;
                cnt = n1.cnt;
            } else {
                mn = n2.mn;
                cnt = n2.cnt;
            }
        }
    }
};

class SegTree {
    private:
    vector<seg_node> arr;
    vector<seg_node> seg;
    int N;

    void build(int node, int x, int y) {
        if (x == y) {
            seg[node] = seg_node(arr[x]);
        } else {
            int m = (x + y) >> 1;
            build(2 * node + 1, x, m);
            build(2 * node + 2, m + 1, y);
            seg[node] = seg_node(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    seg_node query(int node, int x, int y, int l, int r) {
        if (x >= l && y <= r) return seg[node];
        if (r < x || l > y) return seg_node();

        int m = (x + y) >> 1;
        auto left = query(2 * node + 1, x, m, l, r);
        auto right = query(2 * node + 2, m + 1, y, l, r);
        return seg_node(left, right);
    }

    void update(int node, int x, int y, int idx, int val) {
        if (x == y) {
            arr[idx] = val;
            seg[node] = seg_node(arr[idx]);
        } else {
            int m = (x + y) >> 1;
            if (idx >= x && idx <= m) update(2 * node + 1, x, m, idx, val);
            else update(2 * node + 2, m + 1, y, idx, val);
            seg[node] = seg_node(seg[2 * node + 1], seg[2 * node + 2]);
        }
    }

    public:
    SegTree(vector<int64_t>& vec) {
        N = int(vec.size());
        arr.resize(N);
        for (int i = 0; i < N; i++) arr[i] = seg_node(vec[i]);
        seg.resize(4 * N);
        build(0, 0, N - 1);
    }

    seg_node query(int l, int r) {
        return query(0, 0, N - 1, l, r);
    }

    void update(int idx, int val) {
        update(0, 0, N - 1, idx, val);
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
            b--;
            auto [mn, cnt] = seg.query(a, b);
            cout << mn << ' ' << cnt << '\n';
        } else {
            int k, u;
            cin >> k >> u;
            seg.update(k, u);
        }
    }
    return 0;
}
